#include "AnimationState.h"
#include "Animation.h"
#include "AnimControl.h"
#include "AnimRig.h"
#include "Resource.h"
#include "DataDef.h"
#include "Actor.h"

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
    ComponentInstanceData* _data = (ComponentInstanceData*)resource;
    const AnimationStateLayer* _layer = (const AnimationStateLayer*)_data->m_resource;
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
    m_curStateIndex = -1;
    m_lastStateIndex = -1;

    Actor* actor = g_actorWorld.get_actor(id);
    ENGINE_ASSERT_ARGS(actor, "actor not exist %x", id);
    AnimRigInstance* rig = (AnimRigInstance*)actor->get_first_component_of(EngineTypes::ANIMATION_RIG);
    ENGINE_ASSERT(rig, "actor must have anim-rig component");
    m_skeleton = rig->m_skeleton;
    ENGINE_ASSERT(m_skeleton, "rig skeleton not created!");

    change_state(m_stateNames[0]);
}

void AnimationStateLayer::update( float dt )
{
    int _state = m_state;
    switch(_state)
    {
    case kLayerDefault:
        update_default(dt);
        break;
    case kLayerCrossFading:
        update_crossfading(dt);
        break;
    case kLayerWaitingAlign:
        update_waitingalign(dt);
        break;
    default:
        break;
    }
}

void AnimationStateLayer::update_default( float dt )
{
    int _index = m_curStateIndex;
    if(_index < 0)
        return;
    m_states[_index].update(m_weight, dt);
}

void AnimationStateLayer::update_crossfading( float dt )
{
    hk_anim_ctrl* c1 = m_easeInCtrl;
    hk_anim_ctrl* c2 = m_easeOutCtrl;
    c1->update(dt);
    c2->update(dt);

    float _w = m_weight;
    float _w1 = c1->getWeight() * _w;
    float _w2 = c2->getWeight() * _w;

    AnimationState* _states = m_states;
    AnimationState* _cur_state = _states + m_curStateIndex;
    AnimationState* _last_state = _states + m_lastStateIndex;

    _cur_state->update(_w1, dt);
    _last_state->update(_w2, dt);

#ifdef HAVOK_COMPILE
    hk_anim_ctrl::EaseStatus status1 = c1->getEaseStatus();
    hk_anim_ctrl::EaseStatus status2 = c2->getEaseStatus();
    if(status1 == hk_anim_ctrl::EASED_IN &&
       status2 == hk_anim_ctrl::EASED_OUT)
    {
        // crossfading finished!
        m_state = kLayerDefault;
        m_curTransition = NULL;
        _last_state->remove_from_skeleton(m_skeleton);
        _last_state = NULL;
    }
#endif
}

void AnimationStateLayer::update_waitingalign(float dt)
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

void AnimationStateLayer::change_state(AnimationTranstion* t)
{
    int _new_index = t->m_dstStateIndex;
    int _old_index = m_curStateIndex;

    if(_new_index == _old_index)
        return;

    AnimationState* _states = m_states;
    AnimationState* _new_state = _new_index >= 0 ? m_states + _new_index : 0;
    AnimationState* _old_state = _old_index >= 0 ? m_states + _old_index : 0;

    if(_old_state)
        _old_state->on_exit(_new_state, t);

    if(_new_state)
        _new_state->on_enter(m_skeleton, _old_state, t);

    m_lastStateIndex = _old_index;
    m_curStateIndex = _new_index;
    m_curTransition = t;
    m_state = kLayerCrossFading;
    float _time = t->m_duration;
    int _easeType = t->m_easeType;
    m_easeInCtrl->ease_in(_time, _easeType);
    m_easeOutCtrl->ease_out(_time, _easeType);
}

void AnimationStateLayer::change_state( StringId name )
{
    int _index = find_state(name);
    if(_index < 0)
        return;
    static AnimationTranstion t = { 0.1f,  (uint16_t)-1, kEaseCurveSmooth, kMotionBlendingDefault};
    t.m_dstStateIndex = _index;
    change_state(&t);
}

void AnimationStateLayer::fire_event( StringId name )
{
    int _cur_index = m_curStateIndex;
    if(_cur_index < 0)
        return;
    AnimationState* _cur_state = m_states + _cur_index;
    int _index = _cur_state->find_transition(name);
    if(_index < 0)
        return;
    change_state(_cur_state->m_transitions + _index);
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
    AnimationState* _states = m_states;
    AnimationState* _cur_state = _states + m_curStateIndex;
    AnimationState* _last_state = _states + m_lastStateIndex;

#ifdef HAVOK_COMPILE
    int _state = (int)m_curTransition->m_motionBlendingType;
    switch (_state)
    {
    case kMotionBlendingDefault:
    default:
        m_skeleton->getDeltaReferenceFrame(deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreSrcMotion:
        _cur_state->get_root_motion(deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreDstMotion:
        _last_state->get_root_motion(deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreSrcRotation:
        {
            hkQsTransformf motionSrc, motionDst;
            _cur_state->get_root_motion(deltaTime, motionDst);
            _last_state->get_root_motion(deltaTime, motionSrc);
            motionSrc.m_rotation.setIdentity();
            deltaMotionOut.setMul(motionSrc, motionDst);
        }
        break;
    case kMotionBlendingIgnoreDstRotation:
        {
            hkQsTransformf motionSrc, motionDst;
            _cur_state->get_root_motion(deltaTime, motionDst);
            _last_state->get_root_motion(deltaTime, motionSrc);
            motionDst.m_rotation.setIdentity();
            deltaMotionOut.setMul(motionSrc, motionDst);
        }
        break;
    }
#endif
}

void* load_animation_state(void* data, uint32_t size)
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

void lookup_animation_state(void* resource)
{
    AnimationStateLayer* _layer = (AnimationStateLayer*)resource;
    _layer->lookup();
}


















