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

void AnimationStatesInstance::update( float dt )
{
    int s = m_status;
    switch(s)
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

void AnimationStatesInstance::update_default( float dt )
{
    int _index = m_state_index;
    if(_index < 0)
        return;
    m_states[_index].update(m_weight, dt);
    update_node()
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

const AnimationTranstion* get_transtions( const AnimationState* _state )
{
    return (const AnimationTranstion*)((char*)_state + _state->m_transition_offset);
}

const AnimationData* get_animations( const AnimationState* _state )
{
    return (const AnimationData*)((char*)_state + _state->m_animation_offset);
}

int find_transition(const AnimationState* _state, StringId _name)
{
    StringId* _names = (StringId*)((char*)_state + _state->m_transition_name_offset);
    uint32_t _num = _state->m_num_transitions;
    FIND_IN_ARRAY_RET(_names, _num, _name);
}

int find_node(const AnimationState* _state, StringId _name)
{
    StringId* _names = (StringId*)((char*)_state + _state->m_node_name_offset);
    uint32_t _num = _state->m_num_nodes;
    FIND_IN_ARRAY_RET(_names, _num, _name);
}

void* get_node(const AnimationState* _state, uint32_t i)
{
    return (char*)_state + ((uint32_t*)((char*)_state + _state->m_node_key_offset))[i];
}

typedef void (*func_update_node_t)(const void*, const AnimationState*, float, char*);
static func_update_node_t func[AnimationNodeType::Num] =
{
    update_value_node,
    update_lerp_node,
    update_additive_node,
    update_select_node,
};

INTERNAL void update_node_recursive(const void* n, const AnimationState* s, float f, char* d)
{
    func[*((uint32_t*)n)](n, s, f, d);
}

INTERNAL void update_lerp_node(const void* n, const AnimationState* s, float f, char* d)
{
    const LerpNode* lerp = (const LerpNode*)node;
    float w = *((float*)(d + lerp->m_dynamic_data_offset));
    update_node_recursive(get_node(s, lerp->m_left), f*w, d);
    update_node_recursive(get_node(s, lerp->m_right), f*(1-w), d);
}

INTERNAL void update_additive_node(const void* n, const AnimationState* s, float f, char* d)
{
    const AdditiveNode* lerp = (const AdditiveNode*)node;
    float w = *((float*) d + lerp->m_dynamic_data_offset);
    update_node_recursive(get_node(s, lerp->m_left), f*w, d);
    update_node_recursive(get_node(s, lerp->m_right), f*1, d);
}

INTERNAL void update_value_node(const void* n, const AnimationState* s, float f, char* d)
{
    const ValueNode* value = (const ValueNode*)n;
    hk_anim_ctrl* ac = (hk_anim_ctrl*)(d + value->m_dynamic_data_offset);
    ac->set_weight(f);
}

INTERNAL void update_select_node(const void* n, const AnimationState* s, float f, char* d)
{
    const SelectNode* select = (const SelectNode*)n;
    int i = *((int*)(d + select->m_dynamic_data_offset));
    uint32_t num = select->m_num_children;
    uint32_t* indices = (uint32_t*)(char*)select + sizeof(SelectNode));
    float weights[32];
    memset(weights, 0x00, sizeof(weights));
    weights[i] = 1.0f;
    for (uint32_t i=0; i<num; ++i)
    {
        update_node_recursive(get_node(s, indices[i]), s, weights[i] * f, d);
    }
}

void update_node(const AnimationState* state, uint32_t i, float f, char* data)
{
    update_node_recursive(get_node(state, i), f, data);
}

int find_state(const AnimationStates* states, StringId name)
{
    StringId* _names = (StringId*)((char*)states + states->m_state_name_offset);
    uint32_t _num = _state->m_num_states;
    FIND_IN_ARRAY_RET(_names, _num, name);
}

const AnimationState* get_state(const AnimationStates* states, int i)
{
    char* p = (char*)states;
    uint32_t* offsets = p + states->m_state_key_offset;
    return (const AnimationState*)(states + offsets[i]);
}

void lookup_animation_states( void* data)
{
    AnimationStates* states = (AnimationStates*)data;
    char* p = (char*)states;
    uint32_t num = states->m_num_states;
    uint32_t* offsets = p + states->m_state_key_offset;
    for(uint32_t i=0; i<num; ++i)
    {
        AnimationState* state = (AnimationState*)(p + offsets[i]);
        AnimationData* anims = (AnimationData*)((char*)state + state->m_animation_offset);
        uint32_t anim_num = state->m_num_animations;
        for (uint32_t j=0; j<anim_num; ++j)
        {
            anims[j].m_animation = FIND_RESOURCE(Animation, EngineTypes::ANIMATION, anims[j].m_name);
        }
    }
}


















