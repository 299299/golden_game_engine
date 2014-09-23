#pragma once
#include "Prerequisites.h"
#include "StringId.h"

class hkLoader;
class hkpPhysicsData;
class hkpPhysicsSystem;
class hkpRigidBody;

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
    kSystemRBOnly,
    kSystemRagdoll,
    kSystemTrigger,
    kSystemComplex,
    kPhysicsSystemNUM
};

#define MAX_PHYSICS_SYSTEM_NUM      (6)
ENGINE_NATIVE_ALIGN struct PhysicsInstance
{
    void*                       m_data[MAX_PHYSICS_SYSTEM_NUM];
    const PhysicsResource*      m_resource;
    uint8_t                     m_numData;
    uint8_t                     m_systemType;
    bool                        m_dirty;
    bool                        m_inWorld;

    void init(const void* resource);
    void destroy();
    void set_transform(const hkQsTransform& t);
    void set_transform(const hkTransform& t);
    void add_to_simulation();
    void remove_from_simulation();
    void post_simulation(hkpRigidBody* rb);
    void fetch_transfrom(int index, hkTransform& outT);
};