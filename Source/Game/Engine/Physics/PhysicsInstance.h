#pragma once
#include "StringId.h"

class hkLoader;
class hkpPhysicsData;
class hkpPhysicsSystem;
class hkpRigidBody;
class hkTransformf;

ENGINE_NATIVE_ALIGN struct PhysicsResource
{
    DECLARE_RESOURCE(physics);

    hkpPhysicsData*             m_data;
    uint32_t                    m_havokDataOffset;
    uint32_t                    m_havokDataSize;
    uint8_t                     m_systemType;
    char                        m_padding[3];
};

enum PhysicsSystemType
{
    kSystemRigidBody,
    kSystemRagdoll,
    kSystemTrigger,
    kSystemComplex,
    kPhysicsSystemNUM
};


ENGINE_NATIVE_ALIGN struct PhysicsInstance
{
    union
    {
        hkpRigidBody*               m_rigidBody;
        hkpPhysicsSystem*           m_system;
    };

    const PhysicsResource*      m_resource;
    ActorId32                   m_actor;
    uint8_t                     m_numData;
    uint8_t                     m_systemType;
    bool                        m_dirty;
    bool                        m_inWorld;

    void init(const void* resource, ActorId32 actor);
    void destroy();
    void set_transform(const hkTransformf& t);
    void add_to_simulation();
    void remove_from_simulation();
    void post_simulation(hkpRigidBody* rb);
    void fetch_transform(int index, hkTransformf& outT);
};