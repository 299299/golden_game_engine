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
    DECLARE_RESOURCE(states);

    /*
        COLD DATA
    */
    uint32_t                    m_memorySize;
    uint32_t                    m_numStates;
    StringId*                   m_stateNames;
    AnimationState*             m_states;

    /*
        HOT DATA
    */
    float                       m_weight;
    AnimationState*             m_curState;
    AnimationState*             m_lastState;
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

    void fireEvent(StringId name);
    void changeState(StringId name);
    void get_root_motion(float deltaTime, hkQsTransformf& deltaMotionOut);

private:
    void changeState(AnimationTranstion* t);
    void updateDefault(float dt);
    void updateCrossFading(float dt);
    void updateWaitingForAlign(float dt);
    void get_root_motion_crossfading(float deltaTime, hkQsTransformf& deltaMotionOut);
};
