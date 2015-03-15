#pragma once
#include "StringId.h"

class hkLoader;
class hkpPhysicsData;
class hkpPhysicsSystem;
class hkpRigidBody;
class hkTransformf;

ENGINE_NATIVE_ALIGN(struct) PhysicsResource
{
    hkpPhysicsData*             m_data;
    uint32_t                    m_havok_data_offset;
    uint32_t                    m_havok_data_size;
    uint32_t                    m_system_type;
};

enum PhysicsSystemType
{
    kSystemRigidBody,
    kSystemRagdoll,
    kSystemTrigger,
    kSystemComplex,
    kPhysicsSystemNUM
};

struct PhysicsInstance
{
    union
    {
        hkpRigidBody*               m_rigid_body;
        hkpPhysicsSystem*           m_system;
    };

    const PhysicsResource*          m_resource;
    ActorId32                       m_actor;

    int                             m_in_world;
    int                             m_type;

    void init(const void* resource, ActorId32 actor);
    void destroy();
    void set_transform(const hkTransformf& t);
    void add_to_simulation();
    void remove_from_simulation();
    void fetch_transform(int index, hkTransformf& outT);
};


void* load_resource_physics( void* data, uint32_t size );
void  destroy_resource_physics( void* resource );