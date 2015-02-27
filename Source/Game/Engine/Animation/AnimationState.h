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
    uint16_t                    m_dstStateIndex;
    uint8_t                     m_easeType;
    uint8_t                     m_motionBlendingType;
};

struct LerpNode
{
    uint32_t                    m_type;
    uint32_t                    m_dynamic_data_offset;
    uint16_t                    m_left;
    uint16_t                    m_right;
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
};

struct AnimationState
{
    // TRANSITION FILED
    uint32_t                    m_num_transitions;
    uint32_t                    m_transition_name_offset;
    uint32_t                    m_transition_offset;

    // NODE FILED
    uint32_t                    m_num_nodes;
    uint32_t                    m_node_name_offset;
    uint32_t                    m_node_key_offset;
    uint32_t                    m_node_offset;

    // ANIMATION FILED
    uint32_t                    m_num_animations;
    uint32_t                    m_animation_offset;

    // PROPERTY
    bool                        m_looped;
    char                        m_padding[3];
};

const AnimationTranstion* get_transtions(const AnimationState* _state);
const AnimationData* get_animations(const AnimationState* _state);
int find_transition(const AnimationState* _state, StringId _name);
int find_node(const AnimationState* _state, StringId _name);
void* get_node(const AnimationState* _state, uint32_t i);
void  update_node(const AnimationState* _state, uint32_t i, float f, char* data);

struct AnimationStates
{
    uint32_t                m_num_states;
    uint32_t                m_state_offset;
    uint32_t                m_dynamic_data_size;
};

struct AnimationStatesInstance
{
    const AnimationStates*              m_resource;
    float                               m_weight;
    int                                 m_curStateIndex;
    int                                 m_lastStateIndex;
    const AnimationTranstion*           m_curTransition;
    hk_anim_ctrl*                       m_easeInCtrl;
    hk_anim_ctrl*                       m_easeOutCtrl;
    int                                 m_state;
    hkaAnimatedSkeleton*                m_skeleton;

    int  find_state(StringId name);
    void lookup();

    void init(const void* resource, ActorId32 id);
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
};


void* load_animation_states(void*, uint32_t);
void  lookup_animation_states(void*);