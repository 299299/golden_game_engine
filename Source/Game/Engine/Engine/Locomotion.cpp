#include "Locomotion.h"
#include "AnimationState.h"
#include "Actor.h"
#include "DataDef.h"
#include "MathDefs.h"
#include "DebugDraw.h"

typedef int (*func_update_locomotion_state_t)(Locomotion*, const LocomotionInput&, AnimationStatesInstance*, Actor*);

static void apply_root_motion(AnimationStatesInstance *s, hkQsTransform& t, float dt)
{
    hkQsTransform deltaMotion;
    s->get_rootmotion(dt, deltaMotion);
    t.setMulEq(deltaMotion);
}

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

    hkQsTransform t = a->m_transform;
    apply_root_motion(s, t, input.m_dt);

    hkVector4 up;
    up.set(0, 1, 0);

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


func_update_locomotion_state_t s_funcs[kLocomotionStateNum] =
{
    update_idle_state,
    update_move_state,
};

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

    hkVector4 start, end;
    start = a->m_transform.m_translation;

    hkVector4 normal;
    normal.set(0,1,0);
    float raidus = 0.5f;
    g_debugDrawMgr.add_cycle(start, normal, raidus, RGBCOLOR(175,100,50), false);

    float cur_angle = get_up_axis_angle(a->m_transform.m_rotation);
    end.set(hkMath::sin(cur_angle) * raidus, 0, hkMath::cos(cur_angle) * raidus);
    end.add(a->m_transform.m_translation);
    g_debugDrawMgr.add_line(start, end, RGBCOLOR(200,200,0), false);

    float desireAngle = l->m_desireAngle;
    end.set(hkMath::sin(desireAngle) * raidus, 0, hkMath::cos(desireAngle) * raidus);
    end.add(a->m_transform.m_translation);
    g_debugDrawMgr.add_line(start, end, RGBCOLOR(200,0,2000), false);
}