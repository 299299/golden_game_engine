#pragma once
#include "Prerequisites.h"
#include "StringId.h"


ENGINE_NATIVE_ALIGN struct MovementInstance
{
    DECLARE_RESOURCE(movement);

    hkVector4                       m_linearVelocity;
    float                           m_rotateSpeed;
    ActorId32                       m_actor;
    float                           m_motionWeight;
    float                           m_velocityWeight;
    
    void init(const void* resource, ActorId32 actor);
};


enum LocomotionState
{
    kLocomotion_Stand,
    kLocomotion_StandToMove,
    kLocomotion_Move,
    kLocomotion_MoveToStand,
    //
};

ENGINE_NATIVE_ALIGN struct Locomotion
{
    uint8_t                         m_state;
    char                            m_padding[3];
};

struct Actor;
struct MovementManager
{
    void move_characters(Actor* actors, uint32_t num, float dt);
};

extern MovementManager g_moveMgr;
