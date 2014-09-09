#pragma once
#include "Prerequisites.h"


enum LocomotionState
{
    kLocomotion_Stand = 0,
    kLocomotion_Move,
    kLocomotion_Move_Turn_180,
    kLocomotion_Stand_To_Move,
    kLocomotion_Move_To_Stand,
    kLocomotion_InAir,
    kLocomotion_Dying,
    kLocomotion_Dead,
    kLocomotion_Unknow,
    kLocomotion_MAX = 0xFF
};

struct LocomotionInput
{
    hkVector4               m_moveDir;
    float                   m_moveVelocity;
    void reset()
    {
        m_moveDir.setZero4();
        m_moveVelocity = 0.0f;
    }
};

struct ProxyInstance;
struct AnimFSMInstance;
struct Locomotion
{
    void init();
    void update(float dt, hkQsTransform& worldFromModel);

    LocomotionInput                     m_input;
    hkVector4                           m_horizontalDisplacement;
    float                               m_verticalDisplacement;
    float                               m_turnAngleFrameDelta;
    ProxyInstance*                      m_proxy;
    AnimFSMInstance*                    m_fsm;

    uint8_t                             m_state;
    char                                m_padding[3];

private:
    void updateState(float dt);
    void applyState(float dt, hkQsTransform& worldFromModel);
};