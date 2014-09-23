#include "PhysicsInstance.h"
#include "PhysicsWorld.h"
#include "Utils.h"
#include "Log.h"
#include "PhysicsAutoLock.h"
#include "EngineAssert.h"
//==================================================================
#include <Physics2012/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
//==================================================================

void PhysicsInstance::init(const void* resource)
{
    hkpRigidBody* tmp_rbs[20];

    m_resource = (const PhysicsResource*)resource;
    m_inWorld = false;

    const hkpPhysicsData* phyData = m_resource->m_data;
    m_systemType = m_resource->m_systemType;
    switch(m_systemType)
    {
    case kSystemRBOnly:
        {
            int numOfRbs = 0;
            for(int i=0; i < phyData->getPhysicsSystems().getSize(); ++i)
            {
                const hkpPhysicsSystem* sys = phyData->getPhysicsSystems()[i];
                for(int j=0; j<sys->getRigidBodies().getSize(); ++j)
                    tmp_rbs[numOfRbs++] = sys->getRigidBodies()[j];
            }

            m_numData = numOfRbs;
            ENGINE_ASSERT(m_numData <= MAX_PHYSICS_SYSTEM_NUM, "physics num overflow = %d", m_numData);
            for(int i=0; i<m_numData; ++i)
            {
                hkpRigidBody* rb = tmp_rbs[i]->clone();
                rb->setUserData((hkUlong)this);
                m_data[i] = rb;
            }
            break;
        }
    case kSystemTrigger:
        //@TODO:
        break;
    case kSystemRagdoll:
    case kSystemComplex:
        {
            m_numData = phyData->getPhysicsSystems().getSize();
            ENGINE_ASSERT(m_numData <= MAX_PHYSICS_SYSTEM_NUM, "physics num overflow = %d", m_numData);
            for(int i=0; i < m_numData; ++i)
            {
                m_data[i] = phyData->getPhysicsSystems()[i]->clone(hkpPhysicsSystem::CLONE_DEFAULT);
            }
            break;    
        }
    }
    addToSimulation();
}

void PhysicsInstance::set_transfrom(const hkQsTransform& t)
{
    hkTransform tm;
    t.copyToTransformNoScale(tm);
    setTransform(tm);
}

void PhysicsInstance::set_transfrom(const hkTransform& t)
{
    PHYSICS_LOCKWRITE(g_physicsWorld.world());
    switch(m_systemType)
    {
    case kSystemRBOnly:
        {
            ((hkpRigidBody*)m_data[0])->setTransform(t);
        }
        break;

    default:
        break;
    }
}
    
void PhysicsInstance::destroy()
{   
    remove_from_simulation();
    switch(m_systemType)
    {
    case kSystemRBOnly:
        {
            for(int i=0; i < m_numData; ++i)
            {
                hkpRigidBody* rb = (hkpRigidBody*)m_data[i];
                SAFE_REMOVEREF(rb);
                m_data[i] = 0;
            }
        }
        break;
    case kSystemTrigger:
        break;
    case kSystemComplex:
    case kSystemRagdoll:
        {
            for(int i=0; i < m_numData; ++i)
            {
                hkpPhysicsSystem* sys = (hkpPhysicsSystem*)m_data[i];
                SAFE_REMOVEREF(sys);
                m_data[i] = 0;
            }
        }
        break;
    default:
        break;
    }
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
    switch(m_systemType)
    {
    case kSystemRBOnly:
        {
            ((hkpRigidBody*)m_data[index])->approxCurrentTransform(outT);
        }
        break;

    default:
        break;
    }
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
