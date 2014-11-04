#pragma once
#include "Prerequisites.h"


enum MovementState
{
    kMoveByVelocity,
    kMoveByAnimation,
    kMoveByVelocityAndAnimation,
};

ENGINE_NATIVE_ALIGN struct MovementResource 
{
    DECLARE_RESOURCE(movement);
    int                             m_moveState;
};

ENGINE_NATIVE_ALIGN struct MovementInstance
{
    hkVector                        m_velocity;
    float                           m_targetAngle;
    ActorId32                       m_actor;
    int                             m_moveState;
    const MovementResource*         m_resource;
    bool                            m_worldVelocity;
    char                            m_padding[3];
    
    void init(const void* resource, ActorId32 actor);
};

struct Actor;
struct MovementManager
{
    void move_characters(Actor* actors, uint32_t num, float dt);
};

extern MovementManager g_moveMgr;
