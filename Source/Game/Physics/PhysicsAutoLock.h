#pragma once

enum PhysicsLockMode
{
    kLockRead,
    kLockWrite,
    kLockAll
};

class hkpWorld;
class hkpWorldObject;

class  PhysicsAutoLock
{
public:
    PhysicsAutoLock(hkpWorld* world, PhysicsLockMode mode);
    ~PhysicsAutoLock();
private:
    hkpWorld*                   m_world;
    PhysicsLockMode             m_mode;
};

class  ObjectAutoLock
{
public:
    ObjectAutoLock(hkpWorldObject* obj, PhysicsLockMode mode);
    ~ObjectAutoLock();
private:
    hkpWorldObject*                 m_object;
    PhysicsLockMode                 m_mode;
};

void  IgnoreLock(bool bIgnore);

#define PHYSICS_LOCKWRITE(world)\
            PhysicsAutoLock hLock(world,kLockWrite);

#define PHYSICS_LOCKREAD(world)\
            PhysicsAutoLock hLock(world,kLockRead);

#define PHYSICS_LOCK(world)\
            PhysicsAutoLock hLock(world,kLockAll);

#define OBJECT_LOCKWRITE(object)\
            ObjectAutoLock hLock(object,kLockWrite);

#define OBJECT_LOCKREAD(object)\
            ObjectAutoLock hLock(object,kLockRead);
            