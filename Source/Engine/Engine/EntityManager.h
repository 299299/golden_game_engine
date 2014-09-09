#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "DataDef.h"

struct EntityInstance;
struct EntityResource;

class EntityBucket
{
public:
    EntityBucket():m_update(true) {};
    virtual ~EntityBucket() {};
    virtual uint32_t        add_entity(const EntityResource* resource, const hkQsTransform& t) = 0;
    virtual void            remove_entity(uint32_t id) = 0;
    virtual void            prestep_entity(float dt) = 0;   
    virtual void            poststep_entity(float dt) = 0;  
    virtual EntityInstance* lookup_entity(uint32_t id) = 0;
    virtual uint32_t        list_entities(EntityInstance** objects, uint32_t max_size) = 0;
    virtual void            clear() = 0;
    bool    m_update;
};

struct EntityManager
{
    void init();
    void quit();
    void preStep(float dt);
    void postStep(float dt);

    uint32_t   addInstance(const StringId& resName, const hkQsTransform& t);
    uint32_t   addInstance(const EntityResource* resName, const hkQsTransform& t);

    void removeInstance(uint32_t id);
    EntityInstance* lookupInstance(uint32_t id);
    void clearInstances(uint32_t type);
    EntityBucket* getBucket(uint32_t type) { return m_buckets[type]; };

    void setBucketUpdate(int index, bool bUpdate);
    bool isBucketUpdate(int index) const;

private:
    EntityBucket*           m_buckets[kEntityClassNum];
};

extern EntityManager g_entityMgr;