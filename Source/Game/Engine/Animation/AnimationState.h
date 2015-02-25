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

struct AnimationNode
{
    float                       m_factor;
    // animation node, data = animation index in state layer
    // blend nod, data[0] = left child, data[1] = right child
    uint16_t                    m_data[2];
    uint8_t                     m_type;
    char                        m_padding[3];
};

struct AnimationData
{
    Animation*                  m_animation;
    hk_anim_ctrl*               m_control;
    StringId                    m_name;
    float                       m_speed;
};

struct AnimationState
{
    uint32_t                    m_numTransitions;
    StringId*                   m_transitionNames;
    AnimationTranstion*         m_transitions;
    uint32_t                    m_numNodes;
    StringId*                   m_nodeNames;
    AnimationNode*              m_nodes;
    uint32_t                    m_numAnimations;
    AnimationData*              m_animations;

    uint16_t                    m_transitionNameOffset;
    uint16_t                    m_transitionOffset;

    uint16_t                    m_nodeNameOffset;
    uint16_t                    m_nodesOffset;

    uint16_t                    m_animDataOffset;
    bool                        m_loop;
    bool                        m_dirty;

    int find_transition(StringId name);
    int find_node(StringId name);

    // COLD FUNCTION
    void lookup();
    void load(char* _p);

    // HOT FUNCTION
    void init();
    void destroy();
    void on_enter(hkaAnimatedSkeleton* s, AnimationState* _lastState, AnimationTranstion* t);
    void on_exit(AnimationState* _nextState, AnimationTranstion* t);
    void update(float factor, float dt);
    void add_to_skeleton(hkaAnimatedSkeleton* s);
    void remove_from_skeleton(hkaAnimatedSkeleton* s);
    void get_root_motion(float deltaTime, hkQsTransformf& deltaMotionOut);

private:
    void update_node_recursive(AnimationNode* _node, float weight);
};

ENGINE_NATIVE_ALIGN(struct) AnimationStateLayer
{
    /*
        COLD DATA
    */
    uint32_t                    m_memorySize;
    uint32_t                    m_numStates;
    StringId*                   m_stateNames;
    AnimationState*             m_states;
    AnimRig*                    m_rig;
    StringId                    m_rigName;

    /*
        HOT DATA
    */
    float                       m_weight;
    int                         m_curStateIndex;
    int                         m_lastStateIndex;
    AnimationTranstion*         m_curTransition;
    hk_anim_ctrl*               m_easeInCtrl;
    hk_anim_ctrl*               m_easeOutCtrl;
    int                         m_state;
    hkaAnimatedSkeleton*        m_skeleton;

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


void* load_animation_state(void* data, uint32_t);
void  lookup_animation_state(void*);