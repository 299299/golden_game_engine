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
    float               m_vec[2]; // 0 -> horinzontal 1 -> vertical
};

struct Locomotion
{
    int         m_state;
};

void update_locomotion(Locomotion *l, const LocomotionInput &input, ActorId32 id);