#include "AnimationStateCompiler.h"
#include "AnimationState.h"
#include "AnimControl.h"

#define DYNAMIC_ANIM_SIZE (sizeof(hk_anim_ctrl))

extern const char* g_anim_ease_type_names[];
extern const char* g_anim_motion_blending_type_names[];
extern const char* g_anim_node_names[];
extern const char* g_anim_transition_type_names[];
extern const char* g_anim_data_flag_type_names[];

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
        m_transition.m_type = json_to_enum(o, "type", g_anim_transition_type_names, kTransitionCrossFade);
    }
};

struct RuntimeAnimationNode
{
    RuntimeAnimationNode()
    :m_parent(NULL)
    ,m_animation_index(-1)
    ,m_size(0)
    {
    }

    std::vector<RuntimeAnimationNode*>      m_children;
    int                                     m_index;
    int                                     m_type;
    RuntimeAnimationNode*                   m_parent;
    StringId								m_name;
    StringId								m_data_name;
    int                                     m_animation_index;
    int                                     m_size;
    int                                     m_offset;

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
    uint32_t                                m_node_size;
    uint32_t                                m_node_offset;

    RuntimeAnimationState()
    :m_memory(0)
    ,m_node_size(0)
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

        m_state.m_transition_end_index = (uint8_t)-1;
        StringId transition_end = json_to_stringid(o, "transition_end");
        if (transition_end)
        {
            for (size_t i=0; i<m_transitions.size();++i)
            {
                StringId t_name = stringid_caculate(m_transitions[i].m_name.c_str());
                if (t_name == transition_end) {
                    m_state.m_transition_end_index = i;
                    break;
                }
            }
        }

        LOGI("state %s transition-end = %u", m_name.c_str(), m_state.m_transition_end_index);

        //post process
        m_state.m_looped = json_to_bool(o, "looped", true);
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

        m_state.m_node_key_offset = offset;
        offset += sizeof(NodeKey) * m_state.m_num_nodes;

        m_node_offset = offset;
        offset += m_node_size;
        m_memorySize = offset;

        LOGD("state memory-size=%d, node-size=%d", m_memorySize, m_node_size);
    }

    void readNode(const jsonxx::Object& o, RuntimeAnimationNode* node)
    {
        int type = json_to_enum(o, "type", g_anim_node_names, AnimationNodeType::Undefined);
        node->m_type = type;
        node->m_name = json_to_stringid(o, "name");
        m_node_num[type] ++;

        switch(type)
        {
        case AnimationNodeType::Value:
            {
                AnimationData data;
                memset(&data, 0x00, sizeof(data));
                data.m_name = json_to_stringid(o, "animation");
                data.m_speed = json_to_float(o, "speed", 1.0f);
                data.m_crop_start = json_to_float(o, "crop_start", 0.0f);
                data.m_crop_end = json_to_float(o, "crop_end", 0.0f);
                node->m_animation_index = m_animations.size();
                node->m_size = sizeof(ValueNode);
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
                node->m_size = sizeof(BinaryNode);
                node->m_data_name = json_to_stringid(o, "data");
                break;
            }
        case AnimationNodeType::Select:
            {
                const jsonxx::Array& children = o.get<jsonxx::Array>("children");
                for(unsigned i=0; i<children.size(); ++i)
                {
                    const jsonxx::Object& o = children.get<jsonxx::Object>(i);
                    RuntimeAnimationNode* node1 = createNode(node);
                    readNode(o, node1);
                }
                node->m_size = sizeof(SelectNode) + children.size() * sizeof(uint16_t);
                node->m_data_name = json_to_stringid(o, "data");
                break;
            }
        default:
            break;
        }
        m_node_size += node->m_size;
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
            int index = findState(states, m_transitions[i].m_destName);
            ENGINE_ASSERT(index >= 0, "RuntimeAnimationState findStates index != -1");
            m_transitions[i].m_transition.m_next_state_index = index;
        }
    }

    uint32_t findDataKeyOffset(const std::vector<DataKey>& data_keys, StringId name)
    {
        for (size_t i=0; i<data_keys.size();++i)
        {
            if (data_keys[i].m_name == name)
                return data_keys[i].m_offset;
        }
        return 0;
    }

    void prepareMemory(const std::vector<DataKey>& data_keys, int& animation_num)
    {
        m_memory = new char[m_memorySize];
        memset(m_memory, 0x00, m_memorySize);

        char* p = m_memory;

        AnimationState* state = (AnimationState*)p;
        memcpy(p, &m_state, sizeof(m_state));
        p += sizeof(AnimationState);

        state->m_dynamic_animation_offset = animation_num * DYNAMIC_ANIM_SIZE;

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

        NodeKey* node_keys = (NodeKey*)p;
        int current_offset = m_node_offset;
        for (uint32_t i=0; i<m_state.m_num_nodes; ++i)
        {
            node_keys[i].m_name = m_nodes[i]->m_name;
            node_keys[i].m_offset = current_offset;
            m_nodes[i]->m_offset = current_offset;
            current_offset += m_nodes[i]->m_size;
        }
        p += sizeof(NodeKey) * m_state.m_num_nodes;

        for (uint32_t i=0; i<m_state.m_num_nodes; ++i)
        {
            RuntimeAnimationNode* n = m_nodes[i];
            int type = n->m_type;
            *((uint32_t*)p) = type;

            switch(type)
            {
            case AnimationNodeType::Value:
                {
                    ValueNode* v = (ValueNode*)p;
                    v->m_dynamic_data_offset = DYNAMIC_ANIM_SIZE * animation_num;
                    ++animation_num;
                    break;
                }
            case AnimationNodeType::Select:
                {
                    SelectNode* s = (SelectNode*)p;
                    s->m_dynamic_data_offset = findDataKeyOffset(data_keys, n->m_data_name);
                    s->m_num_children = n->m_children.size();
                    uint16_t* child_offsets = (uint16_t*)(p + sizeof(SelectNode));
                    for(uint32_t i=0; i<s->m_num_children; ++i)
                    {
                        int index = n->m_children[i]->m_index;
                        child_offsets[i] = m_nodes[index]->m_offset;
                    }
                    break;
                }
            case AnimationNodeType::Lerp:
            case AnimationNodeType::Additive:
                {
                    BinaryNode* b = (BinaryNode*)p;
                    b->m_dynamic_data_offset = findDataKeyOffset(data_keys, n->m_data_name);
                    int left_index = n->m_children[0]->m_index;
                    int right_index = n->m_children[1]->m_index;
                    ENGINE_ASSERT(left_index != right_index, "AnimationStatets left index == right index!");
                    b->m_left_offset = m_nodes[left_index]->m_offset;
                    b->m_right_offset = m_nodes[right_index]->m_offset;
                    break;
                }
            default:
                continue;
            }

            p += n->m_size;
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

    const jsonxx::Array& jsonDatas = root.get<jsonxx::Array>("data");
    std::vector<DataKey> data_keys;
    data_keys.resize(jsonDatas.size());

    int data_size[kAnimationDataNum] =
    {
        DYNAMIC_ANIM_SIZE,
        sizeof(int32_t),
        sizeof(float),
        sizeof(float)*2,
        sizeof(float)*3,
        sizeof(float)*4,
    };

    int data_offset = 0;
    for (uint32_t i=0; i<jsonDatas.size(); ++i)
    {
        const jsonxx::Object& o = jsonDatas.get<jsonxx::Object>(i);
        data_keys[i].m_name = stringid_caculate(o.get<std::string>("name").c_str());
        data_keys[i].m_flag = json_to_enum(o, "flag", g_anim_data_flag_type_names, 0);
        data_keys[i].m_offset = data_offset;
        data_offset += data_size[data_keys[i].m_flag];
    };

    const jsonxx::Array& jsonStates = root.get<jsonxx::Array>("states");
    std::vector<RuntimeAnimationState> states;
    states.resize(jsonStates.size());

    int total_nums[AnimationNodeType::Num] = {0};
    for (uint32_t i=0; i<jsonStates.size(); ++i)
    {
        const jsonxx::Object& o = jsonStates.get<jsonxx::Object>(i);
        states[i].readJSON(o);
        for(int j=0; j<AnimationNodeType::Num; ++j)
        {
            total_nums[j] += states[i].m_node_num[j];
        }
    }

    int animation_data_size = total_nums[AnimationNodeType::Value] * DYNAMIC_ANIM_SIZE;
    int dynamic_data_size = animation_data_size + data_offset;
    LOGI("dynamic_data_size=%d(animation_data_size=%d,data_offset=%d)", dynamic_data_size, animation_data_size, data_offset);

    // offset data offsets expcept animation
    for (size_t i=0; i<data_keys.size(); ++i)
    {
        data_keys[i].m_offset += animation_data_size;
    }

    int animation_num = 0;
    for (uint32_t i = 0; i <jsonStates.size(); ++i)
    {
        states[i].findStates(states);
        states[i].prepareMemory(data_keys, animation_num);
    }

    uint32_t memSize = sizeof(AnimationStates);
    memSize += sizeof(StateKey) * jsonStates.size();
    memSize += sizeof(DataKey) * jsonDatas.size();
    for (uint32_t i=0; i<jsonStates.size(); ++i)
    {
        memSize += states[i].m_memorySize;
    }

    uint32_t realSize = memSize;
    memSize = NATIVE_ALGIN_SIZE(memSize);
    LOGI("%s animation states memory size = %d", m_input.c_str(), memSize);

    MemoryBuffer mem(memSize);
    AnimationStates* layer = (AnimationStates*)mem.m_buf;
    layer->m_num_states = jsonStates.size();
    layer->m_num_data = jsonDatas.size();
    layer->m_memory_size = memSize;
    layer->m_dynamic_data_size = dynamic_data_size;
    layer->m_state_key_offset = sizeof(AnimationStates);
    layer->m_data_key_offset = sizeof(AnimationStates) + sizeof(StateKey) * jsonStates.size();

    char* p = mem.m_buf;
    p += sizeof(AnimationStates);

    StateKey* state_keys = (StateKey*)p;
    for(uint32_t i=0; i<jsonStates.size(); ++i)
    {
        state_keys[i].m_name = stringid_caculate(states[i].m_name.c_str());
    }
    p += sizeof(StateKey) * jsonStates.size();

    memcpy(p, &data_keys[0], sizeof(DataKey)*data_keys.size());
    p += sizeof(DataKey) * jsonDatas.size();

    for(uint32_t i=0; i<jsonStates.size(); ++i)
    {
        memcpy(p, states[i].m_memory, states[i].m_memorySize);
        state_keys[i].m_offset = (uint32_t)(p - mem.m_buf);
        p += states[i].m_memorySize;
    }

    ENGINE_ASSERT((uint32_t)(p - mem.m_buf) == realSize, "states compile offset check.");
    bool r = write_file(m_output, mem.m_buf, memSize);

#if 1
    FileReader reader(m_output);
    AnimationStates* p_states = (AnimationStates*)reader.m_buf;
    ENGINE_ASSERT(p_states->m_num_states == layer->m_num_states, "animation states compile check.");
    for (uint32_t i=0; i<p_states->m_num_states; ++i)
    {
        const AnimationState* p_state = get_state(p_states, i);
        const AnimationState* p_state1 = get_state(layer, i);
        ENGINE_ASSERT(!memcmp(p_state, p_state1, sizeof(AnimationState)), "animation states compile check.");
    }
#endif

    return r;
}
