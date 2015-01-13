#include "PhysicsInstance.h"
#include "PhysicsWorld.h"
#include "Utils.h"
#include "Log.h"
#include "PhysicsAutoLock.h"
#ifdef HAVOK_COMPILE
#include <Physics2012/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#endif

void PhysicsInstance::init(const void* resource)
{
    m_resource = (const PhysicsResource*)resource;
    m_inWorld = false;
#ifdef HAVOK_COMPILE
    const hkpPhysicsData* phyData = m_resource->m_data;
    m_systemType = m_resource->m_systemType;
    switch(m_systemType)
    {
    case kSystemRigidBody:
        {
            m_rigidBody = phyData->getPhysicsSystems()[0]->getRigidBodies()[0]->clone();
            m_rigidBody->setUserData((hkUlong)this);
            break;
        }
    case kSystemTrigger: break;
    case kSystemRagdoll:
    case kSystemComplex:
        m_system = phyData->getPhysicsSystems()[0]->clone(); break;
    default: break;
    }
#endif
    add_to_simulation();
}

void PhysicsInstance::set_transform(const hkTransform& t)
{
#ifdef HAVOK_COMPILE
    PHYSICS_LOCKWRITE(g_physicsWorld.world());
    switch(m_systemType)
    {
    case kSystemRigidBody: m_rigidBody->setTransform(t); break;
    default: break;
    }
#endif
}

void PhysicsInstance::destroy()
{
    remove_from_simulation();
#ifdef HAVOK_COMPILE
    switch(m_systemType)
    {
    case kSystemRigidBody: SAFE_REMOVEREF(m_rigidBody); break;
    case kSystemTrigger: break;
    case kSystemComplex:
    case kSystemRagdoll:
        SAFE_REMOVEREF(m_system); break;
    default:
        break;
    }
#endif
}


void PhysicsInstance::add_to_simulation()
{
    if(m_inWorld) return;
    g_physicsWorld.add_to_world(this);
    m_inWorld = true;
}

void PhysicsInstance::remove_from_simulation()
{
    if(!m_inWorld) return;
    g_physicsWorld.remove_from_world(this);
    m_inWorld = false;
}


void PhysicsInstance::post_simulation(hkpRigidBody* rb)
{
    m_dirty = true;
}

void PhysicsInstance::fetch_transform(int index, hkTransform& outT)
{
#ifdef HAVOK_COMPILE
    switch(m_systemType)
    {
    case kSystemRigidBody: m_rigidBody->approxCurrentTransform(outT); break;
    default: break;
    }
#endif
}


void* load_resource_physics( const char* data, uint32_t size )
{
    PhysicsResource* physics = (PhysicsResource*)data;
    char* havokData = (char*)data + physics->m_havokDataOffset;
    physics->m_data = (hkpPhysicsData*)load_havok_inplace(havokData, physics->m_havokDataSize);
    return physics;
}

void destroy_resource_physics( void* resource )
{
    PhysicsResource* physics = (PhysicsResource*)resource;
    char* havokData = (char*)resource + physics->m_havokDataOffset;
    unload_havok_inplace(havokData, physics->m_havokDataSize);
}
