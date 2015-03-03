#include "AnimationStateCompiler.h"
#include "AnimationState.h"
#include "AnimControl.h"

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
        n->m_children.push_back(this);
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
    uint32_t                                m_dynamic_data_size;

    RuntimeAnimationState()
    :m_memory(0)
    ,m_dynamic_data_size(0)
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
        m_state.m_looped = json_to_bool(o, "looped");
        m_state.m_num_transitions = m_transitions.size();
        m_state.m_num_nodes = m_nodes.size();
        m_state.m_num_animations = m_animations.size();
        m_state.m_name = stringid_caculate(m_name.c_str());

        uint32_t offset = sizeof(AnimationState);
        m_state.m_transition_name_offset = offset;
        offset += sizeof(StringId) * m_transitions.size();

        m_state.m_transition_offset = offset;
        offset += sizeof(AnimationTranstion) * m_state.m_num_transitions;

        m_state.m_animation_offset = offset;
        offset += sizeof(AnimationData) * m_state.m_num_animations;

        m_state.m_node_name_offset = sizeof(StringId) * m_nodes.size();
        offset += sizeof(StringId) * m_state.m_num_nodes;

        m_state.m_node_offset = offset;
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

    void prepareMemory(int* total_nums, int* cur_nums)
    {
        m_memory = new char[m_memorySize];
        memset(m_memory, 0x00, m_memorySize);

        char* p = m_memory;

        AnimationState* state = (AnimationState*)p;
        memcpy(p, &m_state, sizeof(m_state));
        p += sizeof(AnimationState);

        state->m_dynamic_animation_offset = cur_nums[AnimationNodeType::Value] * sizeof(hk_anim_ctrl);

        StringId* transiton_names = (StringId*)p;
        for (uint32_t i=0; i<m_state.m_num_transitions; ++i)
        {
            transiton_names[i] = stringid_caculate(m_transitions[i].m_name.c_str());
        }
        p += sizeof(StringId) * m_transitions.size();

        AnimationTranstion* transtions = (AnimationTranstion*)p;
        for (uint32_t i=0; i<m_state.m_num_transitions; ++i)
        {
            transtions[i] = m_transitions[i].m_transition;
        }
        p += sizeof(AnimationTranstion) * m_state.m_num_transitions;

        AnimationData* anims = (AnimationData*)p;
        for (uint32_t i=0; i<m_state.m_num_animations; ++i)
        {
            anims[i] = m_animations[i];
        }
        p += sizeof(AnimationData) * m_state.m_num_animations;

        StringId* node_names = (StringId*)p;
        for (uint32_t i=0; i<m_state.m_num_nodes; ++i)
        {
            node_names[i] = stringid_caculate(m_nodes[i]->m_name.c_str());
        }
        p += sizeof(StringId) * m_state.m_num_nodes;

        int nums[AnimationNodeType::Num] = {0};
        int sizes[AnimationNodeType::Num] =
        {
            sizeof(hk_anim_ctrl),
            sizeof(float),
            sizeof(float),
            sizeof(int)
        };
        int total_sizes[AnimationNodeType::Num];
        for(int i=0; i<AnimationNodeType::Num; ++i)
        {
            total_sizes[i] = sizes[i] * total_nums[i];
        }
        int total_offsets[AnimationNodeType::Num];
        int total_size = 0;
        for(int i=0; i<AnimationNodeType::Num;++i)
        {
            total_offsets[i] = total_size + cur_nums[i] * sizes[i];
            total_size += total_sizes[i];
        }

        int node_offset = state->m_node_offset;
        for (uint32_t i=0; i<m_state.m_num_nodes; ++i)
        {
            RuntimeAnimationNode* n = m_nodes[i];
            int type = n->m_type;
            int& num = nums[type];
            int size = sizes[type];
            int offset = total_offsets[type];
            int dynamic_offset = offset + size * num;

            *((uint32_t*)p) = type;

            switch(type)
            {
            case AnimationNodeType::Value:
                {
                    ValueNode* v = (ValueNode*)p;
                    v->m_dynamic_data_offset = offset + size * n->m_animationIndex;
                    break;
                }
            case AnimationNodeType::Select:
                {
                    SelectNode* s = (SelectNode*)p;
                    s->m_dynamic_data_offset = dynamic_offset;
                    s->m_num_children = n->m_children.size();
                    for(uint32_t i=0; i<s->m_num_children; ++i)
                    {
                        int index = n->m_children[i]->m_index;
                        s->m_child_offsets[i] = node_offset + index * NODE_SIZE;
                    }
                    break;
                }
            case AnimationNodeType::Lerp:
            case AnimationNodeType::Additive:
                {
                    BinaryNode* b = (BinaryNode*)p;
                    b->m_dynamic_data_offset = dynamic_offset;
                    int left_index = n->m_children[0]->m_index;
                    int right_index = n->m_children[1]->m_index;
                    ENGINE_ASSERT(left_index != right_index, "AnimationStatets left index == right index!");
                    b->m_left_offset = node_offset + left_index * NODE_SIZE;
                    b->m_right_offset = node_offset + right_index * NODE_SIZE;
                    break;
                }
            default:
                continue;
            }

            ++num;
            p += NODE_SIZE;
            m_dynamic_data_size += size;
        }

        ENGINE_ASSERT(p == m_memory + m_memorySize, "Animation State Node Offset check");
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

    int total_nums[AnimationNodeType::Num] = {0};
    for (uint32_t i=0; i<numStates; ++i)
    {
        const jsonxx::Object& o = jsonStates.get<jsonxx::Object>(i);
        states[i].readJSON(o);
        for(int j=0; j<AnimationNodeType::Num; ++j)
        {
            total_nums[j] += states[i].m_node_num[j];
        }
    }

    int cur_nums[AnimationNodeType::Num] = {0};
    for (uint32_t i = 0; i <numStates; ++i)
    {
        states[i].findStates(states);
        states[i].prepareMemory(total_nums, cur_nums);
        for(int j=0; j<AnimationNodeType::Num; ++j)
        {
            cur_nums[j] += states[i].m_node_num[j];
        }
    }

    uint32_t memSize = sizeof(AnimationStates);
    memSize += (sizeof(StateKey))* numStates;

    uint32_t dynamicSize = 0;

    for (uint32_t i=0; i<numStates; ++i)
    {
        memSize += states[i].m_memorySize;
        dynamicSize += states[i].m_dynamic_data_size;
    }

    memSize = NATIVE_ALGIN_SIZE(memSize);
    LOGI("%s animation states memory size = %d", m_input.c_str(), memSize);

    MemoryBuffer mem(memSize);
    AnimationStates* layer = (AnimationStates*)mem.m_buf;
    layer->m_num_states = numStates;
    layer->m_memory_size = memSize;
    layer->m_dynamic_data_size = dynamicSize;
    layer->m_state_key_offset = sizeof(AnimationStates);

    char* p = mem.m_buf;
    p += sizeof(AnimationStates);

    StateKey* state_keys = (StateKey*)p;
    for(uint32_t i=0; i<numStates; ++i)
    {
        state_keys[i].m_name = stringid_caculate(states[i].m_name.c_str());
    }
    p += sizeof(StateKey) * numStates;

    for(uint32_t i=0; i<numStates; ++i)
    {
        memcpy(p, states[i].m_memory, states[i].m_memorySize);
        state_keys[i].m_offset = (uint32_t)(p - mem.m_buf);
        p += states[i].m_memorySize;
    }

#if 1
    AnimationStates* p_states = (AnimationStates*)mem.m_buf;
    ENGINE_ASSERT(p_states->m_num_states == layer->m_num_states, "animation states compile check.");
    for (uint32_t i=0; i<p_states->m_num_states; ++i)
    {
        const AnimationState* p_state = get_state(p_states, i);
        const AnimationState* p_state1 = get_state(layer, i);
        ENGINE_ASSERT(p_state == p_state1, "animation states compile check.");
    }
#endif

    return write_file(m_output, mem.m_buf, memSize);
}
