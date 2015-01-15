#include "PhysicsAutoLock.h"
#include "Prerequisites.h"
#ifdef HAVOK_COMPILE
#include <Physics2012/Dynamics/World/hkpWorld.h>
#endif

bool ignoreLock = false;
PhysicsAutoLock::PhysicsAutoLock( hkpWorld* world, PhysicsLockMode mode )
:m_world(world)
,m_mode(mode)
{
    if (ignoreLock)
    {
        return;
    }

#ifdef HAVOK_COMPILE
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
#endif
}

PhysicsAutoLock::~PhysicsAutoLock()
{
    if (ignoreLock)
    {
        return;
    }

#ifdef HAVOK_COMPILE
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
#endif

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

#ifdef HAVOK_COMPILE
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
#endif
}

ObjectAutoLock::~ObjectAutoLock()
{
    if (ignoreLock)
    {
        return;
    }
#ifdef HAVOK_COMPILE
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
#endif
}
