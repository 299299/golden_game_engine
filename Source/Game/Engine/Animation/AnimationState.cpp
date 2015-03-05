#include "AnimationState.h"
#include "Animation.h"
#include "AnimControl.h"
#include "AnimRig.h"
#include "Resource.h"
#include "DataDef.h"
#include "Actor.h"
#include "MemorySystem.h"

enum LayerState
{
    kLayerDefault,
    kLayerCrossFading,
    kLayerWaitingAlign,
    kLayerStateMax
};

const AnimationTranstion* get_transtions( const AnimationState* state )
{
    return (const AnimationTranstion*)((char*)state + state->m_transition_offset);
}

const AnimationData* get_animations( const AnimationState* state )
{
    return (const AnimationData*)((char*)state + state->m_animation_offset);
}

const char* get_nodes(const AnimationState* state)
{
    return ((char*)state + state->m_node_offset);
}

const char* get_node(const AnimationState* state, int i)
{
    return get_nodes(state) + i * NODE_SIZE;
}

int find_transition(const AnimationState* state, StringId name)
{
    StringId* names = (StringId*)((char*)state + state->m_transition_name_offset);
    uint32_t num = state->m_num_transitions;
    FIND_IN_ARRAY_RET(names, num, name);
}

int find_node(const AnimationState* state, StringId name)
{
    StringId* node_keys = (StringId*)((char*)state + state->m_node_name_offset);
    uint32_t num = state->m_num_nodes;
    FIND_IN_ARRAY_RET(node_keys, num, name);
}

INTERNAL void update_node_recursive(const char*, const AnimationState*, float, char*);
INTERNAL void update_lerp_node(const char* n, const AnimationState* s, float f, char* d)
{
    const BinaryNode* node = (const BinaryNode*)n;
    float w = *((float*)(d + node->m_dynamic_data_offset));
    update_node_recursive((char*)s + node->m_left_offset, s, f*w, d);
    update_node_recursive((char*)s + node->m_right_offset, s, f*(1-w), d);
}

INTERNAL void update_additive_node(const char* n, const AnimationState* s, float f, char* d)
{
    const BinaryNode* node = (const BinaryNode*)n;
    float w = *((float*)(d + node->m_dynamic_data_offset));
    update_node_recursive((char*)s + node->m_left_offset, s, f*w, d);
    update_node_recursive((char*)s + node->m_right_offset, s, f, d);
}

INTERNAL void update_value_node(const char* n, const AnimationState* s, float f, char* d)
{
    const ValueNode* node = (const ValueNode*)n;
    hk_anim_ctrl* ac = (hk_anim_ctrl*)(d + node->m_dynamic_data_offset);
    ac->set_weight(f);
}

INTERNAL void update_select_node(const char* n, const AnimationState* s, float f, char* d)
{
    const SelectNode* node = (const SelectNode*)n;
    int num_of_children = node->m_num_children;
    int i = *((int*)(d + node->m_dynamic_data_offset));
    const uint16_t* head = node->m_child_offsets;
    float weights[MAX_CHILDREN_NUM] = {0,0,0,0,0,0,0,0};
    weights[i] = 1.0f;
    for (int i=0; i<num_of_children; ++i)
    {
        update_node_recursive((char*)s + head[i], s, weights[i] * f, d);
    }
}
typedef void (*func_update_node_t)(const char*, const AnimationState*, float, char*);
static func_update_node_t node_func_table[AnimationNodeType::Num] =
{
    update_value_node,
    update_lerp_node,
    update_additive_node,
    update_select_node,
};
INTERNAL void update_node_recursive(const char* n, const AnimationState* s, float f, char* d)
{
    node_func_table[*((const uint32_t*)n)](n, s, f, d);
}


INTERNAL void update_node(const AnimationState* s, int i, float f, char* data)
{
    update_node_recursive(get_node(s, i), s, f, data);
}

INTERNAL void on_state_enter(const AnimationState* state, hkaAnimatedSkeleton* s, char* d)
{
    hk_anim_ctrl* anim_ctls = (hk_anim_ctrl*)(d + state->m_dynamic_animation_offset);
    int num = state->m_num_animations;
    const AnimationData* anim_datas = get_animations(state);

    for (int i=0; i<num; ++i)
    {
        const AnimationData* anim_data = anim_datas + i;
        hk_anim_ctrl* ac = anim_ctls + i;
        ac->setPlaybackSpeed(anim_data->m_speed);
        ac->ease_in(0.0f, kEaseCurveSmooth);
        ac->add_to_skeleton(s);
    }
}

INTERNAL void add_state_from_skeleton(const AnimationState* state, hkaAnimatedSkeleton* s, char* d)
{
    hk_anim_ctrl* anim_ctls = (hk_anim_ctrl*)(d + state->m_dynamic_animation_offset);
    int num = state->m_num_animations;
    for (int i=0; i<num; ++i)
    {
        hk_anim_ctrl* ac = anim_ctls + i;
        ac->remove_from_skeleton(s);
    }
}

INTERNAL void remove_state_from_skeleton(const AnimationState* state, hkaAnimatedSkeleton* s, char* d)
{
    hk_anim_ctrl* anim_ctls = (hk_anim_ctrl*)(d + state->m_dynamic_animation_offset);
    int num = state->m_num_animations;
    for (int i=0; i<num; ++i)
    {
        hk_anim_ctrl* ac = anim_ctls + i;
        ac->remove_from_skeleton(s);
    }
}

INTERNAL void init_state_dynamic_data(const AnimationState* state, char* d)
{
    hk_anim_ctrl* anim_ctls = (hk_anim_ctrl*)(d + state->m_dynamic_animation_offset);
    int num = state->m_num_animations;
    const AnimationData* anim_datas = get_animations(state);

    for (int i=0; i<num; ++i)
    {
        const AnimationData* anim_data = anim_datas + i;
        hk_anim_ctrl* anim_ctl = anim_ctls + i;
#ifdef HAVOK_COMPILE
        hk_anim_ctrl* ac = new (anim_ctl) hk_anim_ctrl(anim_data->m_animation);
        ac->m_name = anim_data->m_name;
        ac->set_loop(state->m_looped);
#endif
    }
}

INTERNAL void destroy_state_dynamic_data(const AnimationState* state, char *d)
{
    hk_anim_ctrl* anim_ctls = (hk_anim_ctrl*)(d + state->m_dynamic_animation_offset);
    int num = state->m_num_animations;

    for (int i=0; i<num; ++i)
    {
        hk_anim_ctrl* ac = anim_ctls + i;
        SAFE_DESTRUCTOR(ac, hk_anim_ctrl);
    }
}

INTERNAL void state_get_rootmotion(const AnimationState* state, char *d, float deltaTime, hkQsTransformf& deltaMotionOut)
{
    hk_anim_ctrl* anim_ctls = (hk_anim_ctrl*)(d + state->m_dynamic_animation_offset);
    int num = state->m_num_animations;

    for (int i=0; i<num; ++i)
    {
        hkQsTransform t;
        hk_anim_ctrl* ac = anim_ctls + i;
        ac->getExtractedMotionDeltaReferenceFrame(deltaTime, t);
#ifdef HAVOK_COMPILE
        deltaMotionOut.setMulEq(t);
#endif
    }
}


//=============================================================================

int find_state(const AnimationStates* states, StringId name)
{
    StateKey* keys = (StateKey*)((char*)states + states->m_state_key_offset);
    int num = states->m_num_states;
    for(int i=0; i<num; ++i)
    {
        if(keys[i].m_name == name)
            return i;
    }
    return -1;
}

const AnimationState* get_state(const AnimationStates* states, int i)
{
    char* p = (char*)states;
    StateKey* keys = (StateKey*)(p + states->m_state_key_offset);
    return (const AnimationState*)(p + keys[i].m_offset);
}

void lookup_animation_states( void* data)
{
    AnimationStates* states = (AnimationStates*)data;
    char* p = (char*)states;
    int num = states->m_num_states;
    StateKey* keys = (StateKey*)(p + states->m_state_key_offset);
    for(int i=0; i<num; ++i)
    {
        AnimationState* state = (AnimationState*)(p + keys[i].m_offset);
        AnimationData* anims = (AnimationData*)((char*)state + state->m_animation_offset);
        uint32_t anim_num = state->m_num_animations;
        for (uint32_t j=0; j<anim_num; ++j)
        {
            anims[j].m_animation = FIND_RESOURCE(Animation, EngineTypes::ANIMATION, anims[j].m_name);
        }
    }
}

//=============================================================================

void AnimationStatesInstance::init(const void* resource, ActorId32 id)
{
    ComponentInstanceData* res = (ComponentInstanceData*)resource;
    const AnimationStates* states = (const AnimationStates*)(res->m_resource);
    char* p = (char*)states;

    m_resource = states;
    int num = states->m_num_states;
    int size = states->m_dynamic_data_size;
    char* d = COMMON_ALLOC(char, size);
    m_dynamic_data = d;
    memset(d, 0x00, size);
    StateKey* keys = (StateKey*)(p + states->m_state_key_offset);
    for(int i=0; i<num; ++i)
    {
        const AnimationState* state = (const AnimationState*)(p + keys[i].m_offset);
        init_state_dynamic_data(state, d);
    }

    m_ease_in_ctl = new hk_anim_ctrl(NULL);
    m_ease_out_ctrl = new hk_anim_ctrl(NULL);
    m_status = kLayerDefault;
    m_weight = 1.0f; // default layer weight is 1.0

    Actor* actor = g_actorWorld.get_actor(id);
    ENGINE_ASSERT_ARGS(actor, "actor not exist %x", id);
    AnimRigInstance* rig = (AnimRigInstance*)actor->get_first_component_of(EngineTypes::ANIMATION_RIG);
    ENGINE_ASSERT(rig, "actor must have anim-rig component");
    m_skeleton = rig->m_skeleton;
    ENGINE_ASSERT(m_skeleton, "rig skeleton not created!");

    change_state(keys[0].m_name);
}

void AnimationStatesInstance::destroy()
{
    const AnimationStates* states = m_resource;
    int num = states->m_num_states;
    char* p = (char*)(states);
    StateKey* keys = (StateKey*)(p + states->m_state_key_offset);
    char* d = m_dynamic_data;

    for(int i=0; i<num; ++i)
    {
        const AnimationState* state = (const AnimationState*)(p + keys[i].m_offset);
        destroy_state_dynamic_data(state, d);
    }

    COMMON_DEALLOC(d);
    SAFE_REMOVEREF(m_ease_in_ctl);
    SAFE_REMOVEREF(m_ease_out_ctrl);
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
    if(!m_state)
        return;

    update_node(m_state, 0, m_weight, m_dynamic_data);
}

void AnimationStatesInstance::update_crossfading( float dt )
{
    hk_anim_ctrl* c1 = m_ease_in_ctl;
    hk_anim_ctrl* c2 = m_ease_out_ctrl;
    c1->update(dt);
    c2->update(dt);

    float w = m_weight;
    float w1 = c1->getWeight() * w;
    float w2 = c2->getWeight() * w;

    const AnimationState* cur_state = m_state;
    const AnimationState* last_state = m_last_state;

    char* d = m_dynamic_data;
    update_node(cur_state, 0, w1, d);

    if(last_state)
        update_node(last_state, 0, w2, d);

#ifdef HAVOK_COMPILE
    hk_anim_ctrl::EaseStatus status1 = c1->getEaseStatus();
    hk_anim_ctrl::EaseStatus status2 = c2->getEaseStatus();
    if(status1 == hk_anim_ctrl::EASED_IN &&
       status2 == hk_anim_ctrl::EASED_OUT)
    {
        // crossfading finished!
        m_status = kLayerDefault;
        if(last_state)
            remove_state_from_skeleton(last_state, m_skeleton, d);
        m_last_state = NULL;
    }
#endif
}

void AnimationStatesInstance::update_waitingalign(float dt)
{
    // FIXME:TODO
}

void AnimationStatesInstance::change_state(const AnimationTranstion* t)
{
    const AnimationState* new_state = get_state(m_resource, t->m_next_state_index);
    const AnimationState* old_state = m_state;

    if(new_state == old_state)
        return;

#if 0
    if(old_state)
        on_state_exit(old_state, ...)
#endif

    if(new_state)
        on_state_enter(new_state, m_skeleton, m_dynamic_data);

    m_last_state = old_state;
    m_state = new_state;
    m_status = kLayerCrossFading;

    float duration = t->m_duration;
    int type = t->m_ease_type;

    // clear their ease status first
    m_ease_in_ctl->easeOut(0.0f);
    m_ease_out_ctrl->easeIn(0.0f);
    m_ease_in_ctl->update(1.0f);
    m_ease_out_ctrl->update(1.0f);

    m_ease_in_ctl->ease_in(duration, type);
    m_ease_out_ctrl->ease_out(duration, type);
    m_motion_blend_type = t->m_motion_blend_type;
}

void AnimationStatesInstance::change_state( StringId name )
{
    int index = find_state(m_resource, name);
    if(index < 0)
        return;
    static AnimationTranstion t = { 0.1f,  (uint16_t)-1, kEaseCurveSmooth, kMotionBlendingDefault};
    t.m_next_state_index = index;
    change_state(&t);
}

void AnimationStatesInstance::fire_event( StringId name )
{
    const AnimationState* s = m_state;
    if(!s)
        return;

    int i = find_transition(s, name);
    if(i<0)
        return;

    change_state(get_transtions(s) + i);
}

void AnimationStatesInstance::get_rootmotion( float deltaTime, hkQsTransformf& deltaMotionOut )
{
#ifdef HAVOK_COMPILE
    int status = m_status;
    switch(status)
    {
    case kLayerDefault:
        {
            m_skeleton->getDeltaReferenceFrame(deltaTime, deltaMotionOut);
        }
        break;
    case kLayerCrossFading:
        {
            get_rootmotion_crossfading(deltaTime, deltaMotionOut);
        }
        break;
    case kLayerWaitingAlign:
        break;
    default:
        break;
    }
#endif
}

void AnimationStatesInstance::get_rootmotion_crossfading(float deltaTime, hkQsTransformf& deltaMotionOut )
{
    const AnimationState* cur_state = m_state;
    const AnimationState* last_state = m_last_state;
    char* d = m_dynamic_data;

#ifdef HAVOK_COMPILE
    int status = m_motion_blend_type;
    switch (status)
    {
    case kMotionBlendingDefault:
    default:
        m_skeleton->getDeltaReferenceFrame(deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreSrcMotion:
        state_get_rootmotion(cur_state, d, deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreDstMotion:
        state_get_rootmotion(last_state, d, deltaTime, deltaMotionOut);
        break;
    case kMotionBlendingIgnoreSrcRotation:
        {
            hkQsTransformf motionSrc, motionDst;
            state_get_rootmotion(cur_state, d, deltaTime, deltaMotionOut);
            state_get_rootmotion(last_state, d, deltaTime, deltaMotionOut);
            motionSrc.m_rotation.setIdentity();
            deltaMotionOut.setMul(motionSrc, motionDst);
        }
        break;
    case kMotionBlendingIgnoreDstRotation:
        {
            hkQsTransformf motionSrc, motionDst;
            state_get_rootmotion(cur_state, d, deltaTime, deltaMotionOut);
            state_get_rootmotion(last_state, d, deltaTime, deltaMotionOut);
            motionDst.m_rotation.setIdentity();
            deltaMotionOut.setMul(motionSrc, motionDst);
        }
        break;
    }
#endif
}

void AnimationStatesInstance::set_node_data(StringId name, void* d, int size)
{
    if(!m_state)
        return;

    int i = find_node(m_state, name);
    if(i < 0)
        return;

    const char* n = get_node(m_state, i);
    int type = *(const uint32_t*)n;
    ENGINE_ASSERT(type != AnimationNodeType::Value, "Can not set data to a value node.");

    uint32_t offset = *((const uint32_t*)n + 1);
    memcpy(m_dynamic_data + offset, d, size);
}










