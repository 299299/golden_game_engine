#include "AnimationState.h"
#include "Animation.h"
#include "AnimControl.h"
#include "AnimRig.h"
#include "Resource.h"

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
        animData.m_animation = FIND_RESOURCE(Animation, animData.m_name);
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

void AnimationState::addToSkeleton( hkaAnimatedSkeleton* s )
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

void AnimationState::removeFromSkeleton( hkaAnimatedSkeleton* s )
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
}

void AnimationStateLayer::update( float dt )
{
    uint32_t _num = m_numStates;
    AnimationState* _states = m_states;
    for (uint32_t i=0; i<_num; ++i)
    {
        //_states[i].update(dt);
    }
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
    AnimationState* newState = t->m_dstStateIndex >= 0 ? m_states + t->m_dstStateIndex : 0;
    if(m_curState == newState)
        return;
    hkaAnimatedSkeleton* s = m_skeleton;
    AnimationState* oldState = m_curState;
    if(oldState)
    {
        oldState->on_exit(newState, t);
    }
    m_curState = newState;
    if(newState)
    {
        newState->on_enter(s, oldState, t);
    }
}

void AnimationStateLayer::changeState( StringId name )
{
    int _index = find_state(name);
    if(_index < 0)
        return;
    static AnimationTranstion t = { 0.1f,  -1, kEaseCurveSmooth, kMotionDefault};
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

void* load_animation_state_layer(const char* data, uint32_t size)
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
    ENGINE_ASSERT((_p + sizeof(AnimationState) * _layer->m_numStates) == (data + _layer->m_memorySize),
        "Animation Layer Load Memory Offset Error.");
    return _layer;
}

void lookup_animation_state_layer(const void* resource)
{
    AnimationStateLayer* _layer = (AnimationStateLayer*)resource;
    _layer->lookup();
}



















