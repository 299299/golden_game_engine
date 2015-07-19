#include "Locomotion.h"
#include "AnimationState.h"
#include "Actor.h"
#include "DataDef.h"

typedef int (*func_update_locomotion_state_t)(Locomotion*, const LocomotionInput&, AnimationStatesInstance*);

static int update_idle_state(Locomotion* l, const  LocomotionInput& input, AnimationStatesInstance *s);
static int update_move_state(Locomotion* l, const  LocomotionInput& input, AnimationStatesInstance *s);

func_update_locomotion_state_t s_funcs[kLocomotionStateNum] =
{
    update_idle_state,
    update_move_state,
};

static int update_idle_state(Locomotion* l, const  LocomotionInput& input, AnimationStatesInstance *s)
{
    float sqrt_move_vec  = input.m_vec[0] * input.m_vec[0] + input.m_vec[1] * input.m_vec[1];
    if (sqrt_move_vec > 0.1f) {
        s->fire_event(stringid_caculate("move"));
        return kLocomotionMove;
    }
    return kLocomotionStand;
}

static int update_move_state(Locomotion* l, const  LocomotionInput& input, AnimationStatesInstance *s)
{
    float sqrt_move_vec  = input.m_vec[0] * input.m_vec[0] + input.m_vec[1] * input.m_vec[1];
    if (sqrt_move_vec < 0.1f) {
        s->fire_event(stringid_caculate("stop"));
        return kLocomotionStand;
    }
    return kLocomotionMove;
}

void update_locomotion(Locomotion *l, const LocomotionInput &input, ActorId32 id)
{
    Actor *a = g_actorWorld.get_actor(id);
    if (!a)
        return;

    AnimationStatesInstance* s = (AnimationStatesInstance*)a->get_first_component_of(EngineTypes::ANIMATION_STATES);
    if (!s)
        return;

    l->m_state = s_funcs[l->m_state] (l, input, s);
}