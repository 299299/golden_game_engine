#include "AnimationState.h"
#include "Animation.h"
#include "AnimControl.h"
#include "AnimRig.h"
#include "Resource.h"
#include "DataDef.h"

enum LayerState
{
    kLayerDefault,
    kLayerCrossFading,
    kLayerWaitingAlign,
    kLayerStateMax
};

int AnimationState::find_transition(StringId name)
{
    StringId* _names = m_transitionNames;
    int _num = (int)m_numTransitions;
    FIND_IN_ARRAY_RET(_names, _num, name);
}

int AnimationState::find_node(StringId name)
{
    StringId* _names = m_transitionNames;
    int _num = (int)m_numTransitions;
    FIND_IN_ARRAY_RET(_names, _num, name);
}

void AnimationState::on_enter( hkaAnimatedSkeleton* s, AnimationState* _lastState, AnimationTranstion* t )
{
    uint32_t _num = m_numAnimations;
    AnimationData* _data = m_animations;
    for (uint32_t i=0; i<_num; ++i)
    {
        AnimationData& animData = _data[i];
        hk_anim_ctrl* ac = animData.m_control;
        ac->setLocalTime(0.0f);
        ac->setPlaybackSpeed(animData.m_speed);
        ac->setUnderflowCount(0);
        ac->setOverflowCount(0);
        ac->add_to_skeleton(s);
    }
}

void AnimationState::on_exit( AnimationState* _nextState, AnimationTranstion* t )
{

}

void AnimationState::update( float factor, float dt )
{
    if(!m_dirty)
        return;
    update_node_recursive(m_nodes, factor);
}

void AnimationState::lookup()
{
    uint32_t _num = m_numAnimations;
    AnimationData* _data = m_animations;
    for (uint32_t i=0; i<_num; ++i)
    {
        AnimationData& animData = _data[i];
        animData.m_animation = FIND_RESOURCE(Animation, EngineTypes::ANIMATION, animData.m_name);
    }
}

void AnimationState::init()
{
    uint32_t _num = m_numAnimations;
    AnimationData* _data = m_animations;
    bool _looped = m_loop;
    for(uint32_t i=0; i<_num; ++i)
    {
        AnimationData& animData = _data[i];
        animData.m_control = new hk_anim_ctrl(animData.m_animation);
        animData.m_control->set_loop(_looped);
    }
}

void AnimationState::destroy()
{
    uint32_t _num = m_numAnimations;
    AnimationData* _data = m_animations;
    for(uint32_t i=0; i<_num; ++i)
    {
        AnimationData& animData = _data[i];
        SAFE_REMOVEREF(animData.m_control);
    }
}

void AnimationState::update_node_recursive( AnimationNode* _node, float weight )
{
    int _type = _node->m_type;
    uint32_t _data0 = _node->m_data[0];
    uint32_t _data1 = _node->m_data[1];
    float _factor = _node->m_factor;
    switch(_type)
    {
    case BlendNodeType::Value:
        {
            AnimationData& animData = m_animations[_data0];
            hk_anim_ctrl* ac = animData.m_control;
            ac->set_weight(weight);
        }
        break;
    case BlendNodeType::Lerp:
        {
            AnimationNode* _child0 = m_nodes + _data0;
            AnimationNode* _child1 = m_nodes + _data1;
            update_node_recursive(_child0, weight * _factor);
            update_node_recursive(_node, weight * (1.0f-_factor));
        }
        break;
    case BlendNodeType::Additive:
        {
            AnimationNode* _child0 = m_nodes + _data0;
            AnimationNode* _child1 = m_nodes + _data1;
            update_node_recursive(_child0, weight * _factor);
            update_node_recursive(_node, weight);
        }
        break;
    default:
        break;
    }
}

void AnimationState::load( char* _p )
{
    m_transitionNames = (StringId*)(_p + m_transitionNameOffset);
    m_transitions = (AnimationTranstion*)(_p + m_transitionOffset);
    m_nodeNames = (StringId*)(_p + m_nodeNameOffset);
    m_nodes = (AnimationNode*)(_p + m_nodesOffset);
    m_animations = (AnimationData*)(_p + m_animDataOffset);
}

void AnimationState::add_to_skeleton( hkaAnimatedSkeleton* s )
{
    uint32_t _num = m_numAnimations;
    AnimationData* _data = m_animations;
    for(uint32_t i=0; i<_num; ++i)
    {
        AnimationData& animData = _data[i];
        hk_anim_ctrl* ac = animData.m_control;
        ac->add_to_skeleton(s);
    }
}

void AnimationState::remove_from_skeleton( hkaAnimatedSkeleton* s )
{
    uint32_t _num = m_numAnimations;
    AnimationData* _data = m_animations;
    for(uint32_t i=0; i<_num; ++i)
    {
        AnimationData& animData = _data[i];
        hk_anim_ctrl* ac = animData.m_control;
        ac->remove_from_skeleton(s);
    }
}

void AnimationState::get_root_motion(float deltaTime, hkQsTransformf& deltaMotionOut)
{
#ifdef HAVOK_COMPILE
    uint32_t _num = m_numAnimations;
    AnimationData* _data = m_animations;
    for(uint32_t i=0; i<_num; ++i)
    {
        AnimationData& animData = _data[i];
        hk_anim_ctrl* ac = animData.m_control;
        hkQsTransform t;
        ac->getExtractedMotionDeltaReferenceFrame(deltaTime, t);
        deltaMotionOut.setMulEq(t);
    }
#endif
}

int AnimationStateLayer::find_state(StringId name)
{
    StringId* _names = m_stateNames;
    int _num = (int)m_numStates;
    FIND_IN_ARRAY_RET(_names, _num, name);
}

void AnimationStateLayer::lookup()
{
    uint32_t _num = m_numStates;
    AnimationState* _states = m_states;
    for (uint32_t i=0; i<_num; ++i)
    {
        _states[i].lookup();
    }
    m_rig = FIND_RESOURCE(AnimRig, EngineTypes::ANIMATION_RIG, m_rigName);
    ENGINE_ASSERT(m_rig, "Animtion Rig Not Found!");
}

void AnimationStateLayer::init( const void* resource, ActorId32 id )
{
    const AnimationStateLayer* _layer = (const AnimationStateLayer*)resource;
    memcpy(this, resource, _layer->m_memorySize);
    // TADA!
    uint32_t _num = m_numStates;
    AnimationState* _states = m_states;
    for (uint32_t i=0; i<_num; ++i)
    {
        AnimationState* _state = _states + i;
        _state->init();
        _state->load((char*)_state);
    }

    m_easeInCtrl = new hk_anim_ctrl(NULL);
    m_easeOutCtrl = new hk_anim_ctrl(NULL);
    m_state = kLayerDefault;
}

void AnimationStateLayer::update( float dt )
{
    int _state = m_state;
    switch(_state)
    {
    case kLayerDefault:
        updateDefault(dt);
        break;
    case kLayerCrossFading:
        updateCrossFading(dt);
        break;
    case kLayerWaitingAlign:
        updateWaitingForAlign(dt);
        break;
    default:
        break;
    }
}

void AnimationStateLayer::updateDefault( float dt )
{
    if (m_curState)
        m_curState->update(m_weight, dt);
}

void AnimationStateLayer::updateCrossFading( float dt )
{
    hk_anim_ctrl* c1 = m_easeInCtrl;
    hk_anim_ctrl* c2 = m_easeOutCtrl;
    c1->update(dt);
    c2->update(dt);

    float _w = m_weight;
    float _w1 = c1->getWeight() * _w;
    float _w2 = c2->getWeight() * _w;
    m_curState->update(_w1, dt);
    m_lastState->update(_w2, dt);

#ifdef HAVOK_COMPILE
    hk_anim_ctrl::EaseStatus status1 = c1->getEaseStatus();
    hk_anim_ctrl::EaseStatus status2 = c2->getEaseStatus();
    if(status1 == hk_anim_ctrl::EASED_IN &&
       status2 == hk_anim_ctrl::EASED_OUT)
    {
        // crossfading finished!
        m_state = kLayerDefault;
        m_curTransition = NULL;
        m_lastState->remove_from_skeleton(m_skeleton);
        m_lastState = NULL;
    }
#endif
}

void AnimationStateLayer::updateWaitingForAlign(float dt)
{
    // FIXME:TODO
}

void AnimationStateLayer::destroy()
{
    uint32_t _num = m_numStates;
    AnimationState* _states = m_states;
    for (uint32_t i=0; i<_num; ++i)
    {
        _states[i].destroy();
    }
    SAFE_REMOVEREF(m_easeInCtrl);
    SAFE_REMOVEREF(m_easeOutCtrl);
}

void AnimationStateLayer::changeState(AnimationTranstion* t)
{
    int _index = t->m_dstStateIndex;
    AnimationState* newState = _index >= 0 ? m_states + _index : 0;
    if(m_curState == newState)
        return;
    AnimationState* oldState = m_curState;
    if(oldState)
    {
        oldState->on_exit(newState, t);
    }
    if(newState)
    {
        newState->on_enter(m_skeleton, oldState, t);
    }
    m_lastState = oldState;
    m_curState = newState;
    m_curTransition = t;
    m_state = kLayerCrossFading;
    float _time = t->m_duration;
    int _easeType = t->m_easeType;
    m_easeInCtrl->ease_in(_time, _easeType);
    m_easeOutCtrl->ease_out(_time, _easeType);
}

void AnimationStateLayer::changeState( StringId name )
{
    int _index = find_state(name);
    if(_index < 0)
        return;
    static AnimationTranstion t = { 0.1f,  (uint16_t)-1, kEaseCurveSmooth, kMotionBlendingDefault};
    t.m_dstStateIndex = _index;
    changeState(&t);
}

void AnimationStateLayer::fireEvent( StringId name )
{
    if(!m_curState)
        return;
    int _index = m_curState->find_transition(name);
    if(_index < 0)
        return;
    changeState(m_curState->m_transitions + _index);
}

void AnimationStateLayer::get_root_motion( float deltaTime, hkQsTransformf& deltaMotionOut )
{
#ifdef HAVOK_COMPILE
    int _state = m_state;
    switch(_state)
    {
    case kLayerDefault:
        {
            m_skeleton->getDeltaReferenceFrame(deltaTime, deltaMotionOut);
        }
        break;
    case kLayerCrossFading:
        {
            get_root_motion_crossfading(deltaTime, deltaMotionOut);
        }
        break;
    case kLayerWaitingAlign:
        break;
    default:
        break;
    }
#endif
}

void AnimationStateLayer::get_root_motion_crossfading(float deltaTime, hkQsTransformf& deltaMotionOut )
{
#ifdef HAVOK_COMPILE
    int _state = (int)m_curTransition->m_motionBlendingType;
    switch (_state)
    {
    case kMotionBlendingDefault:
    default:
        m_skeleton->getDeltaReferenceFrame(deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreSrcMotion:
        m_curState->get_root_motion(deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreDstMotion:
        m_lastState->get_root_motion(deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreSrcRotation:
        {
            hkQsTransformf motionSrc, motionDst;
            m_curState->get_root_motion(deltaTime, motionDst);
            m_lastState->get_root_motion(deltaTime, motionSrc);
            motionSrc.m_rotation.setIdentity();
            deltaMotionOut.setMul(motionSrc, motionDst);
        }
        break;
    case kMotionBlendingIgnoreDstRotation:
        {
            hkQsTransformf motionSrc, motionDst;
            m_curState->get_root_motion(deltaTime, motionDst);
            m_lastState->get_root_motion(deltaTime, motionSrc);
            motionDst.m_rotation.setIdentity();
            deltaMotionOut.setMul(motionSrc, motionDst);
        }
        break;
    }
#endif
}

void* load_animation_state_layer(void* data, uint32_t size)
{
    AnimationStateLayer* _layer = (AnimationStateLayer*)data;
    char* _p = (char*)data;
    _p += sizeof(AnimationStateLayer);
    _layer->m_stateNames = (StringId*)_p;
    _p += sizeof(StringId) * _layer->m_numStates;
    _layer->m_states = (AnimationState*)_p;

    uint32_t _num = _layer->m_numStates;
    for (uint32_t i=0; i<_num; ++i)
    {
        _layer->m_states[i].load((char*)data);
    }
    return _layer;
}

void lookup_animation_state_layer(void* resource)
{
    AnimationStateLayer* _layer = (AnimationStateLayer*)resource;
    _layer->lookup();
}



















