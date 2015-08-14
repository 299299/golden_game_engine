#pragma once
#include "Prerequisites.h"
#include "StringId.h"

struct Animation;
struct hk_anim_ctrl;
struct AnimRig;
class  hkaAnimatedSkeleton;
class  hkQsTransformf;

struct AnimationTranstion
{
    float                       m_duration;
    uint8_t                     m_next_state_index;
    uint8_t                     m_ease_type;
    uint8_t                     m_motion_blend_type;
    uint8_t                     m_type;
};

struct AnimationData
{
    Animation*                  m_animation;
    StringId                    m_name;
    float                       m_speed;
    float                       m_crop_start;
    float                       m_crop_end;
};

struct NodeKey
{
    StringId                    m_name;
    uint32_t                    m_offset;
};

struct BinaryNode
{
    uint32_t                    m_type;
    uint32_t                    m_dynamic_data_offset;
    uint32_t                    m_left_offset;
    uint32_t                    m_right_offset;
};

struct ValueNode
{
    uint32_t                    m_type;
    uint32_t                    m_dynamic_data_offset;
};

struct SelectNode
{
    uint32_t                    m_type;
    uint32_t                    m_dynamic_data_offset;
    uint32_t                    m_num_children;
    // uint16_t                    m_child_offsets[MAX_CHILDREN_NUM];
};

struct AnimationState
{
    // TRANSITION FILED
    uint32_t                    m_num_transitions;
    uint32_t                    m_transition_name_offset;
    uint32_t                    m_transition_offset;

    // ANIMATION FILED
    uint32_t                    m_num_animations;
    uint32_t                    m_animation_offset;
    uint32_t                    m_dynamic_animation_offset;

    // NODE FILED
    uint32_t                    m_num_nodes;
    uint32_t                    m_node_key_offset;

    // PROPERTY
    StringId                    m_name;
    bool                        m_looped;
    char                        m_padding[3];
};

struct StateKey
{
    StringId                    m_name;
    uint32_t                    m_offset;
};

struct AnimationStates
{
    uint32_t                    m_num_states;
    uint32_t                    m_state_key_offset;
    uint32_t                    m_dynamic_data_size;
    uint32_t                    m_memory_size;
};

struct AnimationStatesInstance
{
    const AnimationStates*              m_resource;
    float                               m_weight;
    const AnimationState*               m_state;
    const AnimationState*               m_last_state;
    hk_anim_ctrl*                       m_ease_in_ctl;
    hk_anim_ctrl*                       m_ease_out_ctrl;
    int                                 m_status;
    int                                 m_motion_blend_type;
    hkaAnimatedSkeleton*                m_skeleton;
    char*                               m_dynamic_data;
    int                                 m_dirty;
    ActorId32                           m_actor;

    void init(const void*, ActorId32);
    void update(float dt);
    void destroy();
    void reset();

    void fire_event(StringId name);
    void change_state(StringId name);
    void get_rootmotion(float deltaTime, hkQsTransformf& deltaMotionOut);
    void set_node_data(StringId name, void* d, int size);
    void set_node_data(StringId state_name, StringId name, void* d, int size);

private:
    void change_state(const AnimationTranstion* t);
    void update_default(float dt);
    void update_crossfading(float dt);
    void update_waitingalign(float dt);
    void update_frozen(float dt);
    void get_rootmotion_crossfading(float deltaTime, hkQsTransformf& deltaMotionOut);
    void set_node_data(const AnimationState *state, StringId name, void* d, int size);
};

const AnimationState* get_state(const AnimationStates*, int);
void  lookup_animation_states(void*);