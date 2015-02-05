#include "AnimationStateCompiler.h"
#include "AnimationState.h"

extern const char* g_anim_ease_type_names[];
extern const char* g_anim_motion_blending_type_names[];
extern const char* g_anim_node_names[];

struct RuntimeAnimationTransition
{
    AnimationTranstion                      m_transition;
    std::string                             m_destName;
    std::string                             m_name;

    void readJSON(const jsonxx::Object& o)
    {
        m_name = o.get<std::string>("name");
        m_destName = o.get<std::string>("dest");
        m_transition.m_duration = json_to_float(o, "duration", DEFAULT_ANIM_TRANSITION_DURATION);
        m_transition.m_easeType = json_to_enum(o, "ease", g_anim_ease_type_names, kEaseCurveSmooth);
        m_transition.m_motionBlendingType = json_to_enum(o, "motion_blending", g_anim_motion_blending_type_names, kMotionBlendingDefault);
    }
};

struct RuntimeAnimationNode
{
    RuntimeAnimationNode()
    {
        m_left = m_right = m_parent = 0;
        memset(&m_node, 0x00, sizeof(m_node));
        m_animationIndex = -1;
    }

    AnimationNode                           m_node;
    RuntimeAnimationNode*                   m_left;
    RuntimeAnimationNode*                   m_right;
    RuntimeAnimationNode*                   m_parent;
    std::string                             m_animationName;
    std::string                             m_name;
    int                                     m_animationIndex;
};


struct RuntimeAnimationState
{
    AnimationState                          m_state;
    std::vector<RuntimeAnimationTransition> m_transitions;
    std::vector<RuntimeAnimationNode*>      m_nodes;
    std::vector<AnimationData>              m_animations;
    std::string                             m_name;
    uint32_t                                m_memorySize;

    RuntimeAnimationState()
    {
        memset(&m_state, 0x00, sizeof(m_state));
    }

    ~RuntimeAnimationState()
    {
        for (size_t i=0; i<m_nodes.size(); ++i)
        {
            delete m_nodes[i];
        }
    }

    void readJSON(const jsonxx::Object& o)
    {
        m_name = o.get<std::string>("name");
        const jsonxx::Array& transitions = o.get<jsonxx::Array>("transitions");
        m_transitions.resize(transitions.size());
        for (uint32_t i=0; i<m_transitions.size(); ++i)
        {
            const jsonxx::Object& jsonT = transitions.get<jsonxx::Object>(i);
            m_transitions[i].readJSON(jsonT);
        }

        if(!o.has<jsonxx::Object>("nodes"))
            return;
        const jsonxx::Object& jsonNodes = o.get<jsonxx::Object>("nodes");
        RuntimeAnimationNode* node = new RuntimeAnimationNode;
        m_nodes.push_back(node);
        readNode(jsonNodes, node);

        //post process
        m_memorySize = (sizeof(AnimationTranstion) + sizeof(StringId)) * m_transitions.size() +
                       (sizeof(AnimationNode) + sizeof(StringId)) * m_nodes.size() +
                       sizeof(AnimationData) * m_animations.size();
        m_state.m_loop = json_to_bool(o, "looped");
        m_state.m_numTransitions = m_transitions.size();
        m_state.m_numNodes = m_nodes.size();
        m_state.m_numAnimations = m_animations.size();
        uint32_t offset = 0;
        m_state.m_transitionNameOffset = offset;
        offset += sizeof(StringId) * m_transitions.size();
        m_state.m_transitionOffset = offset;
        offset += sizeof(AnimationTranstion) * m_transitions.size();
        m_state.m_nodeNameOffset = sizeof(StringId) * m_nodes.size();
        offset += sizeof(StringId) * m_nodes.size();
        m_state.m_nodesOffset = offset;
        offset += sizeof(AnimationNode) * m_nodes.size();
        m_state.m_animDataOffset = offset;
    }

    void readNode(const jsonxx::Object& o, RuntimeAnimationNode* node)
    {
        int type = json_to_enum(o, "type", g_anim_node_names, BlendNodeType::Undefined);
        node->m_node.m_type = type;
        node->m_name = o.get<std::string>("name");

        switch(type)
        {
        case BlendNodeType::Value:
            {
                node->m_animationName = o.get<std::string>("animation");
                AnimationData data;
                memset(&data, 0x00, sizeof(data));
                data.m_name = stringid_caculate(node->m_animationName.c_str());
                data.m_speed = json_to_float(o, "speed", 1.0f);
                node->m_animationIndex = m_animations.size();
                m_animations.push_back(data);
                break;
            }
        case BlendNodeType::Lerp:
        case BlendNodeType::Additive:
            {
                const jsonxx::Object& o1 = o.get<jsonxx::Object>("left");
                const jsonxx::Object& o2 = o.get<jsonxx::Object>("right");
                RuntimeAnimationNode* node1 = new RuntimeAnimationNode;
                RuntimeAnimationNode* node2 = new RuntimeAnimationNode;
                m_nodes.push_back(node1);
                m_nodes.push_back(node2);
                int index_1 = m_nodes.size() - 2;
                int index_2 = m_nodes.size() - 1;
                node1->m_parent = node;
                node2->m_parent = node;
                node->m_left = node1;
                node->m_right = node2;
                node->m_node.m_data[0] = index_1;
                node->m_node.m_data[1] = index_2;
                readNode(o1, node1);
                readNode(o2, node2);
                break;
            }
        default:
            break;
        }
    }

    int findState(const std::vector<RuntimeAnimationState>& states, const std::string& name)
    {
        for (size_t i=0; i<states.size(); ++i)
        {
            if(states[i].m_name == name)
                return i;
        }
        return -1;
    }

    void findStates(const std::vector<RuntimeAnimationState>& states)
    {
        for (size_t i=0; i<m_transitions.size(); ++i)
        {
            m_transitions[i].m_transition.m_dstStateIndex = findState(states, m_transitions[i].m_destName);
        }
    }

    void fillState(AnimationState& state, uint32_t memOffset, char* head) const
    {
        memcpy(&state, &m_state, sizeof(AnimationState));
        state.m_transitionNameOffset += memOffset;
        state.m_transitionOffset += memOffset;
        state.m_nodeNameOffset += memOffset;
        state.m_nodesOffset += memOffset;
        state.m_animDataOffset += memOffset;
        state.load(head);
        for (uint32_t i=0; i<state.m_numTransitions; ++i)
        {
            state.m_transitions[i] = m_transitions[i].m_transition;
            state.m_transitionNames[i] = stringid_caculate(m_transitions[i].m_name.c_str());
        }
        for (uint32_t i=0; i<state.m_numNodes; ++i)
        {
            state.m_nodeNames[i] = stringid_caculate(m_nodes[i]->m_name.c_str());
            state.m_nodes[i] = m_nodes[i]->m_node;
        }
        for (uint32_t i=0; i<state.m_numAnimations; ++i)
        {
            state.m_animations[i] = m_animations[i];
        }
    }
};


AnimationStateCompiler::AnimationStateCompiler()
{

}

AnimationStateCompiler::~AnimationStateCompiler()
{

}

bool AnimationStateCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);

    const jsonxx::Array& jsonStates = root.get<jsonxx::Array>("states");
    uint32_t numStates = jsonStates.size();
    std::vector<RuntimeAnimationState> states;
    states.resize(numStates);

    for (uint32_t i=0; i<numStates; ++i)
    {
        const jsonxx::Object& o = jsonStates.get<jsonxx::Object>(i);
        states[i].readJSON(o);
    }

    uint32_t memSize = sizeof(AnimationStateLayer);
    memSize += (sizeof(StringId) + sizeof(AnimationState))* numStates;
    for (uint32_t i=0; i<numStates; ++i)
    {
        states[i].findStates(states);
        memSize += states[i].m_memorySize;
    }

    memSize = NEXT_MULTIPLE_OF(16, memSize);
    MemoryBuffer mem(memSize);
    AnimationStateLayer* layer = (AnimationStateLayer*)mem.m_buf;
    layer->m_numStates = numStates;
    layer->m_memorySize = memSize;
    char* p = mem.m_buf;
    p += sizeof(AnimationStateLayer);
    layer->m_stateNames = (StringId*)p;
    p += sizeof(StringId) * layer->m_numStates;
    layer->m_states = (AnimationState*)p;
    p += sizeof(AnimationState) * layer->m_numStates;
    uint32_t memOffset = (uint32_t)(p - mem.m_buf);

    for(uint32_t i=0; i<numStates; ++i)
    {
        const RuntimeAnimationState& rtState = states[i];
        layer->m_stateNames[i] = stringid_caculate(rtState.m_name.c_str());
        AnimationState& state = layer->m_states[i];
        rtState.fillState(state, memOffset, mem.m_buf);
        memOffset += rtState.m_memorySize;
    }

#if 1
    extern void* load_animation_state_layer(const char*, uint32_t);
    AnimationStateLayer* l = (AnimationStateLayer*)load_animation_state_layer(mem.m_buf, mem.m_size);
    ENGINE_ASSERT(l->m_numStates == numStates, "AnimationStateLayer load check");
    for(uint32_t i=0; i<numStates; ++i)
    {
        const AnimationState& state = l->m_states[i];
        const RuntimeAnimationState& state2 = states[i];
        ENGINE_ASSERT(l->m_stateNames[i] == stringid_caculate(state2.m_name.c_str()), "AnimationStateLayer load check");
        ENGINE_ASSERT(state.m_numAnimations == state2.m_animations.size(), "AnimationStateLayer load check");
        ENGINE_ASSERT(state.m_numNodes == state2.m_nodes.size(), "AnimationStateLayer load check");
        ENGINE_ASSERT(state.m_numTransitions == state2.m_transitions.size(), "AnimationStateLayer load check");
        for (uint32_t j=0; j<state.m_numNodes; ++j)
        {
            ENGINE_ASSERT(state.m_nodeNames[j] == stringid_caculate(state2.m_nodes[j]->m_name.c_str()),
                "AnimationStateLayer load check");
        }
        for (uint32_t j=0; j<state.m_numTransitions; ++j)
        {
            ENGINE_ASSERT(state.m_transitionNames[j] == stringid_caculate(state2.m_transitions[j].m_name.c_str()),
                "AnimationStateLayer load check");
        }
        for (uint32_t j=0; j<state.m_numAnimations; ++j)
        {
            ENGINE_ASSERT(state.m_animations[j].m_name == state2.m_animations[j].m_name,
                "AnimationStateLayer load check");
        }
    }
#endif
    return write_file(m_output, mem.m_buf, memSize);
}
