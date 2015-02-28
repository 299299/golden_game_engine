#pragma once
#include "Prerequisites.h"
#include "StringId.h"

struct Animation;
struct hk_anim_ctrl;
struct AnimRig;
class  hkaAnimatedSkeleton;
class  hkQsTransformf;

#define NODE_SIZE           32
#define MAX_CHILDREN_NUM    8

// lerp node layout  ---> uint32 | uint32 | uint32 | uint32
// type | offset_of_left_child | offset_of_right_child | offset_of_dynamic_factor

// value node layout  ---> uint32 | uint32
// type | offset_of_dynamic_animation_addr

// select node layout ---> uint32 | uint32 | uint32 | uint16 | uint16...
// note max 8 children
// type | offset_of_index_addr | num_of_animations | child_node_offset_0 | child_node_offset_1...

struct AnimationTranstion
{
    float                       m_duration;
    uint16_t                    m_dstStateIndex;
    uint8_t                     m_easeType;
    uint8_t                     m_motionBlendingType;
};

struct AnimationData
{
    Animation*                  m_animation;
    StringId                    m_name;
    float                       m_speed;
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

    // NODE FILED
    uint32_t                    m_num_nodes;
    uint32_t                    m_node_name_offset;
    uint32_t                    m_node_offset;

    // PROPERTY
    bool                        m_looped;
    char                        m_padding[3];
};

const AnimationTranstion* get_transtions(const AnimationState*);
const AnimationData* get_animations(const AnimationState*);
const char* get_nodes(const AnimationState*);
int find_transition(const AnimationState*, StringId);
int find_node(const AnimationState*, StringId);
const char* get_node(const AnimationState*, int i);
void update_node(const AnimationState*, int i, float f, char* data);

struct StateKey
{
    StringId                    m_name;
    uint32_t                    m_offset;
};

struct AnimationStates
{
    uint32_t                    m_num_states;
    uint32_t                    m_state_key_offset;
    uint32_t                    m_num_animations;
    uint32_t                    m_animation_offset;
    uint32_t                    m_dynamic_data_size;
};

int find_state(const AnimationStates* , StringId);
const AnimationState* get_state(const AnimationStates* , int);

struct AnimationStatesInstance
{
    const AnimationStates*              m_resource;
    float                               m_weight;
    const AnimationState*               m_state;
    const AnimationState*               m_last_state;
    const AnimationTranstion*           m_transition;
    hk_anim_ctrl*                       m_ease_in_ctl;
    hk_anim_ctrl*                       m_ease_out_ctrl;
    int                                 m_status;
    hkaAnimatedSkeleton*                m_skeleton;
    char*                               m_dynamic_data;

    void init(const void*, ActorId32);
    void update(float dt);
    void destroy();

    void fire_event(StringId name);
    void change_state(StringId name);
    void get_root_motion(float deltaTime, hkQsTransformf& deltaMotionOut);

private:
    void change_state(AnimationTranstion* t);
    void update_default(float dt);
    void update_crossfading(float dt);
    void update_waitingalign(float dt);
    void get_root_motion_crossfading(float deltaTime, hkQsTransformf& deltaMotionOut);
    void enter_state(AnimationTranstion* t, int last_state, hkaAnimatedSkeleton* s);
};

void  lookup_animation_states(void*);