#pragma once
#include "Prerequisites.h"
#include "StringId.h"

ENGINE_NATIVE_ALIGN struct MovementResource 
{
    DECLARE_RESOURCE(movement);
    int                             m_dummy;
};

ENGINE_NATIVE_ALIGN struct MovementInstance
{
    hkVector4                       m_linearVelocity;
    float                           m_rotateSpeed;
    ActorId32                       m_actor;
    const MovementResource*         m_resource;
    float                           m_motionWeight;
    float                           m_velocityWeight;
    
    void init(const void* resource, ActorId32 actor);
};

struct Actor;
struct MovementManager
{
    void move_characters(Actor* actors, uint32_t num, float dt);
};

extern MovementManager g_moveMgr;
