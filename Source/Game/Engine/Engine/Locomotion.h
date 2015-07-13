#pragma once
#include "Prerequisites.h"

enum LocomotionState
{
    kLocomotionStand,
    kLocomotionMove,


    kLocomotionStateNum
};

struct MovementInput
{
    float                   m_dt;
    hkQsTransform*          m_transform;
    int                     m_state;
};

struct Movement
{
    int         m_state;
    void update(const MovementInput& input);
};