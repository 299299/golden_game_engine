#include "EntityManager.h"
#include "Entity.h"
#include "MemoryPool.h"
#include "Memory.h"
#include "Profiler.h"
#include "DataDef.h"
#include "Resource.h"
#include "Log.h"
//======================================================================================
#include "LevelGeometry.h"
#include "Prop.h"
#include "Character.h"
//======================================================================================

template <class T> 
class EntityDynamicArray : public EntityBucket
{
public:
    DynamicObjectArray<T>           m_objects;

    EntityDynamicArray(int max_num)
    {
        INIT_STATIC_POOL(m_objects, max_num);
    }
    virtual uint32_t        add_entity(const EntityResource* resource, const hkQsTransform& t) 
    {
        T& object = m_objects.addObject();
        object.init(resource);
        object.setTransform(t);
        object.start(t);
        return object.m_id;
    }
    virtual void            remove_entity(uint32_t id) 
    {
        if(!m_objects.has(id)) return;
        T& object = m_objects.lookup(id);
        object.stop();
        object.destroy();
        m_objects.remove(id);
    }
    virtual void            prestep_entity(float dt)
    {
        if(!m_update) return;
        for (uint32_t i=0; i<m_objects.getSize();++i)
        {
            m_objects[i].preStep(dt);
        }
    }
    virtual void            poststep_entity(float dt)
    {
        if(!m_update) return;
        for (uint32_t i=0; i<m_objects.getSize();++i)
        {
            m_objects[i].postStep(dt);
        }
    }
    virtual EntityInstance* lookup_entity(uint32_t id)
    {
        if(!m_objects.has(id)) return 0;
        return &m_objects.lookup(id);
    }
    virtual uint32_t        list_entities(EntityInstance** objects, uint32_t max_size)
    {
        uint32_t retNum = max_size < m_objects.getSize() ? max_size : m_objects.getSize();
        for (uint32_t i=0; i<retNum; ++i)
        {
            objects[i] = &m_objects[i];
        }
        return retNum;
    }
    virtual void            clear()
    {
        for (uint32_t i=0; i<m_objects.getSize();++i)
        {
            m_objects[i].stop();
            m_objects[i].destroy();
        }
        m_objects.clear();
    }
};


EntityManager g_entityMgr;

void EntityManager::init()
{
    memset(m_buckets, 0x00, sizeof(m_buckets));
    m_buckets[kLevelGeometry] = new EntityDynamicArray<LevelGeometry>(1000);
    m_buckets[kProp] = new EntityDynamicArray<Prop>(1000);
    m_buckets[kCharacter] = new EntityDynamicArray<Character>(30);
}

void EntityManager::quit()
{
    for(int i=0; i<kEntityClassNum; ++i) 
    {
        m_buckets[i]->clear();
        delete m_buckets[i];
    }
}

void EntityManager::preStep( float dt )
{
    PROFILE(EntityManager_preStep);
    for(int i=0; i<kEntityClassNum; ++i)
    {
        EntityBucket* bucket = m_buckets[i];
        if(!bucket) continue;
        bucket->prestep_entity(dt);
    }
}

void EntityManager::postStep( float dt  )
{
    PROFILE(EntityManager_postStep);
    for(int i=0; i<kEntityClassNum; ++i)
    {
        EntityBucket* bucket = m_buckets[i];
        if(!bucket) continue;
        bucket->poststep_entity(dt);
    }
}

void EntityManager::clearInstances(uint32_t type)
{
    if(type == INVALID_U32)
    {
        for(int i=0; i<kEntityClassNum; ++i)
        {
            m_buckets[i]->clear();
        }
    }
    else
    {
        m_buckets[type]->clear();
    }
}

uint32_t EntityManager::addInstance(const StringId& resName, const hkQsTransform& t)
{
    EntityResource* res = FIND_RESOURCE(EntityResource, resName);
    if(!res)
    {
        LOGE(__FUNCTION__" can not find entity resource %s", stringid_lookup(resName));
        return INVLIAD_ENTITY_ID;
    }
    return addInstance(res, t);
}

uint32_t EntityManager::addInstance(const EntityResource* res, const hkQsTransform& t)
{
    EntityID entityId;
    entityId.m_class = res->m_class;
    entityId.m_instId = m_buckets[res->m_class]->add_entity(res, t);
    return entityId.encode(); 
}

void EntityManager::removeInstance(uint32_t id)
{
    if(id == INVLIAD_ENTITY_ID)
        return;
    EntityID entityId;
    entityId.decode(id);
    m_buckets[entityId.m_class]->remove_entity(entityId.m_instId);
}

EntityInstance* 
EntityManager::lookupInstance(uint32_t id)
{
    if(id == INVLIAD_ENTITY_ID)
        return 0;
    EntityID entityId;
    entityId.decode(id);
    return m_buckets[entityId.m_class]->lookup_entity(entityId.m_instId);
}

void EntityManager::setBucketUpdate( int index, bool bUpdate )
{
    m_buckets[index]->m_update = bUpdate;
}

bool EntityManager::isBucketUpdate( int index ) const
{
    return m_buckets[index]->m_update;
}
