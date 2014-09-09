#pragma once
#include "Entity.h"

struct ModelInstance;
struct PhysicsInstance;

ENGINE_ALIGN(16) struct Prop : public EntityInstance
{
    int                             m_modelIndex;
    int                             m_physicsIndex;

    ModelInstance*                  m_model;
    PhysicsInstance*                m_physics;

    void start(const hkQsTransform& t);
    void stop();
    void preStep(float dt);
    void postStep(float dt);
};
