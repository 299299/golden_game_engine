#pragma once
#include "Prerequisites.h"
#include "StringId.h"

class hkaDefaultAnimationControl;
typedef hkaDefaultAnimationControl hk_anim_ctrl;
class hkaAnimatedSkeleton;
typedef hkaAnimatedSkeleton hk_anim_skel;

struct Animation;
struct AnimationTrigger;
struct AnimationEvent;

//==========================================================================================
//  RESOURCE
//==========================================================================================

enum BlendCurveType
{
    kBlendCurveSmooth = 0,
    kBlendCurveFast,
    kBlendCurveLinear,
};
enum TransitionMode
{
    kTransitionCrossFade = 0,
    kTransitionFrozen, 
    kTransitionCrossFadeSync,
    kTransitionFrozenSync,
};
enum MotionBlendType
{
    kMotionBlendDefault = 0,
    kMotionBlendIgnoreSrc,
    kMotionBlendIgnoreDst,
    kMotionBlendIgnoreSrcRotation,
    kMotionBlendIgnoreDstRotation,
};
enum StateType
{
    kSimpleState,
    kBlendState,
    kCustomState,
};
enum StateStatus
{
    kStateNormal = 0,
    kStateTransitioning,
    kStateWaitForAlgin,
};

struct State;
ENGINE_NATIVE_ALIGN struct Transition
{
    float               m_duration;
    StringId            m_event;
    StringId            m_beat;
    
    uint8_t             m_destStateIndex;
    uint8_t             m_motionBlendType;
    uint8_t             m_blendCurve;
    uint8_t             m_mode;
};

ENGINE_NATIVE_ALIGN struct State
{
    StringId            m_name;
  
    Transition*         m_transitions;
    Animation**         m_animations;
    StringId*           m_animNames;
      
    uint32_t            m_transitionOffset;
    uint32_t            m_animationOffset;
    uint32_t            m_animNameOffset;
    
    float               m_speed;

    uint8_t             m_numTransitions;
    uint8_t             m_numAnimations;
    uint8_t             m_flags;
    bool                m_looped;
    
    void                lookup();
    const               Transition* find_transition(const StringId& name) const;
    hk_anim_ctrl*       create_anim_ctrl(uint32_t index) const;
};

#define MAX_ANIM_FSM_LAYER_NUM      (8)

ENGINE_NATIVE_ALIGN struct AnimFSMLayer
{
    State*              m_states;
    StringId            m_name;
    uint32_t            m_numStates;
    uint32_t            m_numAnimations;
    uint32_t            m_stateOffset;
    
    void                lookup();
    const               State* find_state(StringId name) const;
};

ENGINE_NATIVE_ALIGN struct AnimFSM
{
    DECLARE_RESOURCE(anim_fsm);

    AnimFSMLayer        m_layers[MAX_ANIM_FSM_LAYER_NUM];
    uint32_t            m_numLayers;
    uint32_t            m_numStates;
    uint32_t            m_numAnimations;

    void                lookup();
};

//==========================================================================================
//  RUNTIME
//==========================================================================================

struct RtState
{
    uint32_t                    m_timeInState;
    hk_anim_ctrl**              m_ctrls;
    float*                      m_weights;
    const State*                m_state;
    uint32_t                    m_numAnimations;
    float                       m_duration;
    
    void init(const State* state);
    void destroy();
    void get_rootmotion(float dt, hkQsTransform& motionOut);
    uint32_t collect_triggers(float dt, AnimationEvent* events);
    
    void add(hk_anim_skel* skeleton, float fLocalTime = 0.0f, float fSpeed = 1.0f);
    void remove(hk_anim_skel* skeleton);
    void set_weight(float fBaseWeight);
    void set_playbackspeed(float fSpeed);
    void set_localtime(float fLocalTime);
    bool is_finished() const;
};

struct RtTransition
{
    hk_anim_ctrl*               m_easeInCtrl;
    hk_anim_ctrl*               m_easeOutCtrl;
    
    RtState*                    m_lastState;
    RtState*                    m_nextState;
    const Transition*           m_transition;

    float                       m_nextTime;
    float                       m_waitAlignTime;
};

struct RtLayer
{
    RtTransition                m_transition;
    RtState*                    m_curState;
    RtState*                    m_states;    
    hk_anim_skel*               m_skeleton;
    const AnimFSMLayer*         m_layer;
    
    float                       m_weight;
    uint8_t                     m_status;
    bool                        m_dirty;
    char                        m_padding[2];
    
    void mark_dirty() { m_dirty = true; };
    void init(const AnimFSMLayer* resource);
    void destroy();
    void udpate(float dt);
    void send_event(const StringId& evtName);
    bool is_state_active(const StringId& stateName) const;
    bool is_in_state(const StringId& stateName) const;
    
    void do_transition(const Transition* t);
    void get_rootmotion(float dt, hkQsTransform& motionOut);
    uint32_t collect_triggers(float dt, AnimationEvent* events);
    
private:
    void change_status(uint8_t newStatus);
    void get_transition_rootmotion(float dt, hkQsTransform& motionOut);
};

struct AnimFSMInstance
{
    RtLayer                     m_layers[MAX_ANIM_FSM_LAYER_NUM];
    const AnimFSM*              m_resource;
    char*                       m_blob;
    ActorId32                   m_actor;
    
    void init(const void* resource);
    void destroy();
    void update(float dt);
    uint32_t collect_triggers(float dt, AnimationEvent* events);
    void send_event(const StringId& evtName, int index = -1);
};

