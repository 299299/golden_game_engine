#include "PhysicsInstance.h"
#include "PhysicsWorld.h"
#include "Utils.h"
#include "Log.h"
#include "PhysicsAutoLock.h"
#include "Prerequisites.h"
#include "DataDef.h"
#ifdef HAVOK_COMPILE
#include <Physics2012/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#endif

void PhysicsInstance::init(const void* resource, ActorId32 actor)
{
    const ComponentInstanceData* d = (const ComponentInstanceData*)resource;
    m_resource = (const PhysicsResource*)(d->m_resource);
    m_actor = actor;
    m_in_world = 0;
    const hkpPhysicsData* phyData = m_resource->m_data;
#ifdef HAVOK_COMPILE
    int sys_type = m_resource->m_system_type;
    m_type = sys_type;
    switch(sys_type)
    {
    case kSystemRigidBody:
        {
            m_rigid_body = phyData->getPhysicsSystems()[0]->getRigidBodies()[0]->clone();
            m_rigid_body->setUserData((hkUlong)this);
            break;
        }
    case kSystemTrigger: break;
    case kSystemRagdoll:
    case kSystemComplex:
        m_system = phyData->getPhysicsSystems()[0]->clone();
        break;
    default:
        break;
    }
#endif
    add_to_simulation();
}

void PhysicsInstance::set_transform(const hkTransform& t)
{
    int type = m_type;
#ifdef HAVOK_COMPILE
    PHYSICS_LOCKWRITE(g_physicsWorld.world());
    switch(type)
    {
    case kSystemRigidBody:
        m_rigid_body->setTransform(t);
        break;
    default:
        break;
    }
#endif
}

void PhysicsInstance::destroy()
{
    remove_from_simulation();
    int type = m_type;
#ifdef HAVOK_COMPILE
    switch(type)
    {
    case kSystemRigidBody:
        SAFE_REMOVEREF(m_rigid_body);
        break;
    case kSystemTrigger:
        break;
    case kSystemComplex:
    case kSystemRagdoll:
        SAFE_REMOVEREF(m_system);
        break;
    default:
        break;
    }
#endif
}


void PhysicsInstance::add_to_simulation()
{
    if(m_in_world)
        return;

    hkpWorld* world = g_physicsWorld.m_world;
    g_physicsWorld.check_status();
    PHYSICS_LOCKWRITE(world);
    int type = m_type;
#ifdef HAVOK_COMPILE
    switch(type)
    {
    case kSystemRigidBody:
        world->addEntity(m_rigid_body);
        break;
    case kSystemRagdoll:
    case kSystemComplex:
        world->addPhysicsSystem(m_system);
        break;
    default:
        break;
    }
#endif

    m_in_world = 1;
}

void PhysicsInstance::remove_from_simulation()
{
    if(!m_in_world)
        return;

    hkpWorld* world = g_physicsWorld.m_world;
    g_physicsWorld.check_status();
    PHYSICS_LOCKWRITE(world);
    int type = m_type;
#ifdef HAVOK_COMPILE
    switch(type)
    {
    case kSystemRigidBody:
        world->removeEntity(m_rigid_body);
        break;
    case kSystemRagdoll:
    case kSystemComplex:
        world->removePhysicsSystem(m_system);
        break;
    default:
        break;
    }
#endif

    m_in_world = 0;
}

void PhysicsInstance::fetch_transform(int index, hkTransform& outT)
{
    int type = m_type;
    switch(type)
    {
    case kSystemRigidBody:
#ifdef HAVOK_COMPILE
        m_rigid_body->approxCurrentTransform(outT);
#endif
        break;
    default:
        break;
    }
}

void* load_resource_physics( void* data, uint32_t size )
{
    PhysicsResource* physics = (PhysicsResource*)data;
    physics->m_data = (hkpPhysicsData*)load_havok_inplace((char*)data + physics->m_havok_data_offset, physics->m_havok_data_size);
    return physics;
}

void destroy_resource_physics( void* resource )
{
    PhysicsResource* physics = (PhysicsResource*)resource;
    unload_havok_inplace((char*)resource + physics->m_havok_data_offset, physics->m_havok_data_size);
}
