#pragma once
#include "Prerequisites.h"
#include "StringId.h"

enum LocomotionState
{
    kLocomotionStand = 0,
    kLocomotionMove,


    kLocomotionStateNum
};

struct LocomotionInput
{
    float               m_dt;
    float               m_moveVec;
    float               m_desireAngle;
};

struct Locomotion
{
    int         m_state;
    float       m_desireAngle;
    float       m_turnSpeed;
};

void update_locomotion(Locomotion *l, const LocomotionInput &input, ActorId32 id);
void debug_draw_locomotion(Locomotion* l);