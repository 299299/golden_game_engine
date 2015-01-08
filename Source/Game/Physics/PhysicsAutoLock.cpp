#include "PhysicsAutoLock.h"
#include "Prerequisites.h"
#include <Physics2012/Dynamics/World/hkpWorld.h>

bool ignoreLock = false;
PhysicsAutoLock::PhysicsAutoLock( hkpWorld* world, PhysicsLockMode mode )
:m_world(world)
,m_mode(mode)
{
    if (ignoreLock)
    {
        return;
    }

    switch (m_mode)
    {
    case kLockRead:
        m_world->markForRead();
        break;
    case kLockWrite:
        m_world->markForWrite();
        break;
    case kLockAll:
        m_world->lock();
        break;
    default:
        break;
    }
}

PhysicsAutoLock::~PhysicsAutoLock()
{
    if (ignoreLock)
    {
        return;
    }

    switch (m_mode)
    {
    case kLockRead:
        m_world->unmarkForRead();
        break;
    case kLockWrite:
        m_world->unmarkForWrite();
        break;
    case kLockAll:
        m_world->unlock();
        break;
    default:
        break;
    }

}

void IgnoreLock( bool bIgnore )
{
    ignoreLock = bIgnore;
}

ObjectAutoLock::ObjectAutoLock( hkpWorldObject* obj, PhysicsLockMode mode )
    :m_object(obj)
    ,m_mode(mode)
{
    if (ignoreLock)
    {
        return;
    }

    switch (m_mode)
    {
    case kLockRead:
        m_object->markForRead();
        break;
    case kLockWrite:
        m_object->markForWrite();
        break;
    default:
        break;
    }

}

ObjectAutoLock::~ObjectAutoLock()
{
    if (ignoreLock)
    {
        return;
    }

    switch (m_mode)
    {
    case kLockRead:
        m_object->unmarkForRead();
        break;
    case kLockWrite:
        m_object->unmarkForWrite();
        break;
    default:
        break;
    }

}
