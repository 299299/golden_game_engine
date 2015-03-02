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
        m_transition.m_ease_type = json_to_enum(o, "ease", g_anim_ease_type_names, kEaseCurveSmooth);
        m_transition.m_motion_blend_type = json_to_enum(o, "motion_blending", g_anim_motion_blending_type_names, kMotionBlendingDefault);
    }
};

struct RuntimeAnimationNode
{
    RuntimeAnimationNode()
    {
        m_parent = 0;
        m_animationIndex = -1;
    }

    std::vector<RuntimeAnimationNode*>      m_children;
    int                                     m_index;
    int                                     m_type;
    RuntimeAnimationNode*                   m_parent;
    std::string                             m_animationName;
    std::string                             m_name;
    int                                     m_animationIndex;

    char                                    m_node[NODE_SIZE];

    void setParent(RuntimeAnimationNode* n)
    {
        n->m_children.push_back(n);
        m_parent = n;
    }
};


struct RuntimeAnimationState
{
    AnimationState                          m_state;
    std::vector<RuntimeAnimationTransition> m_transitions;
    std::vector<RuntimeAnimationNode*>      m_nodes;
    std::vector<AnimationData>              m_animations;
    std::string                             m_name;
    uint32_t                                m_memorySize;
    char*                                   m_memory;
    int                                     m_node_num[AnimationNodeType::Num];

    RuntimeAnimationState()
    :m_memory(0)
    {
        memset(&m_state, 0x00, sizeof(m_state));
        memset(m_node_num, 0x00, sizeof(m_node_num));
    }

    ~RuntimeAnimationState()
    {
        for (size_t i=0; i<m_nodes.size(); ++i)
        {
            delete m_nodes[i];
        }
        delete []m_memory;
    }

    RuntimeAnimationNode* createNode(RuntimeAnimationNode* parent)
    {
        RuntimeAnimationNode* node = new RuntimeAnimationNode;
        node->m_index = m_nodes.size();
        m_nodes.push_back(node);
        if(parent)
            node->setParent(parent);
        return node;
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
        RuntimeAnimationNode* node = createNode(NULL);
        readNode(jsonNodes, node);

        //post process
        m_state.m_loop = json_to_bool(o, "looped");
        m_state.m_num_transitions = m_transitions.size();
        m_state.m_num_nodes = m_nodes.size();
        m_state.m_num_animations = m_animations.size();

        uint32_t offset = sizeof(AnimationState);
        m_state.m_transition_name_offset = offset;
        offset += sizeof(StringId) * m_transitions.size();

        m_state.m_transition_offset = offset;
        offset += sizeof(AnimationTranstion) * m_state.m_num_transitions;

        m_state.m_animation_offset = offset;
        offset += sizeof(AnimationData) * m_state.m_num_animations;

        m_state.m_node_name_offset = sizeof(StringId) * m_nodes.size();
        offset += sizeof(StringId) * m_state.m_num_nodes;

        m_state.m_nodesOffset = offset;
        offset += NODE_SIZE * m_state.m_num_nodes;

        m_memorySize = offset;
    }

    void readNode(const jsonxx::Object& o, RuntimeAnimationNode* node)
    {
        int type = json_to_enum(o, "type", g_anim_node_names, AnimationNodeType::Undefined);
        node->m_type = type;
        node->m_name = o.get<std::string>("name");
        m_node_num[type] ++;

        switch(type)
        {
        case AnimationNodeType::Value:
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
        case AnimationNodeType::Lerp:
        case AnimationNodeType::Additive:
            {
                const jsonxx::Object& o1 = o.get<jsonxx::Object>("left");
                const jsonxx::Object& o2 = o.get<jsonxx::Object>("right");
                RuntimeAnimationNode* node1 = createNode(node);
                RuntimeAnimationNode* node2 = createNode(node);
                readNode(o1, node1);
                readNode(o2, node2);
                break;
            }
        case AnimationNodeType::Select:
            {
                const jsonxx::Array& children = o.get<jsonxx::Array>("children");
                for(unsigned i=0; i<children.size(); ++i)
                {
                    const jsonxx::Object& o = children.get<jsonxx::Object>(i);
                    RuntimeAnimationNode* node = createNode(node);
                    readNode(o, node);
                }
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
            m_transitions[i].m_transition.m_next_state_index = findState(states, m_transitions[i].m_destName);
        }
    }

    void prepareMemory()
    {
        m_memory = new char[m_memorySize];
        char* p = m_memory + sizeof(AnimationState);

        StringId* transiton_names = (StringId*)p;
        for (int i=0; i<m_state.m_num_transitions; ++i)
        {
            transiton_names[i] = stringid_caculate(m_transitions[i].m_name.c_str());
        }
        p += sizeof(StringId) * m_transitions.size();

        AnimationTranstion* transtions = (AnimationTranstion*)p;
        for (int i=0; i<m_state.m_num_transitions; ++i)
        {
            transtions[i] = m_transitions[i].m_transition;
        }
        p += sizeof(AnimationTranstion) * m_state.m_num_transitions;

        AnimationData* anims = (AnimationData*)p;
        for (int i=0; i<m_state.m_num_animations; ++i)
        {
            anims[i] = m_animations[i];
        }
        p += sizeof(AnimationData) * m_state.m_num_animations;

        StringId* node_names = (StringId*)p;
        for (int i=0; i<m_state.m_num_nodes; ++i)
        {
            node_names[i] = stringid_caculate(m_nodes[i]->m_name.c_str());
        }
        p += sizeof(StringId) * m_state.m_num_nodes;

        int nums[AnimationNodeType::Num] = {0};
        int animation_size = m_num_nodes[AnimationNodeType::Value] * sizeof(hk_anim_ctrl);

        for (int i=0; i<m_state.m_num_nodes; ++i)
        {
            RuntimeAnimationNode* n = m_nodes[i];
            int type = n->m_type;

            switch(type)
            {
            case AnimationNodeType::Value:
                break;
            case AnimationNodeType::Select:
                break;
            case AnimationNodeType::Lerp:
            case AnimationNodeType::Additive:
                break;
            default:
                continue;
            }

            p += NODE_SIZE;
        }

        ENGNIE_ASSERT(p == m_memory + m_memorySize, "Animation State Node Offset check");
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

#if 0
    uint32_t memSize = sizeof(AnimationStateLayer);
    memSize += (sizeof(StringId) + sizeof(AnimationState))* numStates;
    for (uint32_t i=0; i<numStates; ++i)
    {
        states[i].findStates(states);
        memSize += states[i].m_memorySize;
    }

    memSize = NATIVE_ALGIN_SIZE(memSize);
    LOGI("%s animation states memory size = %d", m_input.c_str(), memSize);

    MemoryBuffer mem(memSize);
    AnimationStateLayer* layer = (AnimationStateLayer*)mem.m_buf;
    layer->m_numStates = numStates;
    layer->m_memorySize = memSize;
    layer->m_rigName = json_to_stringid(root, "rig");
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


    return write_file(m_output, mem.m_buf, memSize);
#endif
    return 0;
}
