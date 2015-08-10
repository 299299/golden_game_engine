#include "Locomotion.h"
#include "AnimationState.h"
#include "Actor.h"
#include "DataDef.h"
#include "MathDefs.h"
#include "DebugDraw.h"

typedef int (*func_update_locomotion_state_t)(Locomotion*, const LocomotionInput&, AnimationStatesInstance*, Actor*);

static int update_idle_state(Locomotion*, const  LocomotionInput&, AnimationStatesInstance*, Actor*);
static int update_move_state(Locomotion*, const  LocomotionInput&, AnimationStatesInstance*, Actor*);

func_update_locomotion_state_t s_funcs[kLocomotionStateNum] =
{
    update_idle_state,
    update_move_state,
};

static int update_idle_state(Locomotion* l, const  LocomotionInput& input, AnimationStatesInstance *s, Actor* actor)
{
    if (input.m_moveVec > 0.1f) {
        s->fire_event(stringid_caculate("move"));
        return kLocomotionMove;
    }
    return kLocomotionStand;
}

static int update_move_state(Locomotion* l, const  LocomotionInput& input, AnimationStatesInstance *s, Actor* a)
{
    if (input.m_moveVec < 0.1f) {
        s->fire_event(stringid_caculate("stop"));
        return kLocomotionStand;
    }

    hkVector4 up;
    up.set(0, 1, 0);
    hkQsTransform t = a->m_transform;
    float cur_angle = get_up_axis_angle(t.m_rotation);
    float angle_diff = input.m_desireAngle - cur_angle;
    angle_diff = clamp_angle(angle_diff);
    float turn_amount = angle_diff * l->m_turnSpeed * input.m_dt;
    // printf("angle_diff=%f m_desireAngle=%f cur_angle=%f turn_amount=%f\n", angle_diff, input.m_desireAngle, cur_angle, turn_amount);
    hkQuaternion deltaRot;
    deltaRot.setAxisAngle(up, turn_amount);
    t.m_rotation.mul(deltaRot);
    a->set_transform(t);
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

    l->m_desireAngle = input.m_desireAngle;
    l->m_state = s_funcs[l->m_state] (l, input, s, a);
}

void debug_draw_locomotion(Locomotion* l, ActorId32 id)
{
    Actor *a = g_actorWorld.get_actor(id);
    if (!a)
        return;

    float pos[3] = { 0, 0, 0};
    transform_vec3(pos, a->m_transform.m_translation);
    pos[1] -= 1.0f;

    float normal[3] = { 0, 1, 0};
    float raidus = 1.0f;
    g_debugDrawMgr.add_cycle(pos, normal, raidus, RGBCOLOR(200,200,200), false);

    float dst_pos[3] = {0, pos[1], 0};
    float cur_angle = get_up_axis_angle(a->m_transform.m_rotation);
    dst_pos[0] = hkMath::sin(cur_angle) * raidus;
    dst_pos[2] = hkMath::cos(cur_angle) * raidus;
    g_debugDrawMgr.add_line(pos, dst_pos, RGBCOLOR(200,200,0), false);

    float desireAngle = l->m_desireAngle;
    dst_pos[0] = hkMath::sin(desireAngle) * raidus;
    dst_pos[2] = hkMath::cos(desireAngle) * raidus;
    g_debugDrawMgr.add_line(pos, dst_pos, RGBCOLOR(200,0,2000), false);
}