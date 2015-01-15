#include "Actor.h"
#include "Component.h"
#include "IdArray.h"
#include "Resource.h"
#include "Model.h"
#include "Light.h"
#include "Graphics.h"
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "MemorySystem.h"
#include "memory.h"
#include "Utils.h"
#include "DataDef.h"

struct ActorId
{
    uint32_t    m_id       : 16;
    uint32_t    m_index    : 12;
    uint32_t    m_class    : 4;

    void set_id(Id id)
    {
        m_id = id.id;
        ENGINE_ASSERT(id.index < (1 << 12), "ActorId index overflow.!");
        m_index = id.index;
    }

    Id get_id()
    {
        Id id;
        id.id = m_id;
        id.index = m_index;
        return id;
    }

    static ActorId32 pack_actor_id(uint32_t classId, Id indexId)
    {
        ActorId actor_id;
        actor_id.m_class = classId;
        actor_id.set_id(indexId);
        return *((uint32_t*)&actor_id);
    }

    static void unpack_actor_id(const ActorId32& actor_id, uint32_t& classId, Id& indexId)
    {
        ActorId id;
        memcpy(&id, &actor_id, sizeof(ActorId32));
        classId = id.m_class;
        indexId = id.get_id();
    }
};

void* load_resource_actor(const char* data, uint32_t size)
{
    ActorResource* actor = (ActorResource*)data;
    char* p = (char*)data;
    p += sizeof(ActorResource);
    p += actor->m_numComponents * (sizeof(void*) + sizeof(StringId)) * 2;
    Fact& fact = actor->m_fact;
    fact.m_keys = (Key*)(p);
    p += sizeof(actor->m_fact.m_num_keys * sizeof(Key));
    fact.m_values = p;
    return actor;
}


void lookup_resource_actor(void* resource)
{
    ActorResource* actor = (ActorResource*)resource;
    uint32_t num = actor->m_numComponents;
    StringId* types = actor->m_resourceTypes;
    StringId* names = actor->m_resourceNames;
    void** resources = actor->m_resources;
    ComponentFactory** facs = actor->m_factories;
    for (uint32_t i=0; i<actor->m_numComponents; ++i)
    {
        resources[i] = g_resourceMgr.find_resource(types[i], names[i]);
        facs[i] = g_componentMgr.find_factory(types[i]);
    }
}

void Actor::set_transform( const hkQsTransform& t )
{
    m_transform = t;
    
    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_numComponents;
    Id* id = m_components;
    ComponentFactory** facs = resource->m_factories;

    for (uint32_t i=0; i<num; ++i)
    {
        facs[i]->transform_component(id[i], t);
    }
}

void Actor::set_transform_ignore_type( const hkQsTransform& t, const StringId& type )
{
    m_transform = t;

    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_numComponents;
    Id* id = m_components;
    ComponentFactory** facs = resource->m_factories;
    StringId* types = resource->m_resourceTypes;

    for (uint32_t i=0; i<num; ++i)
    {
        if(type != types[i])
            facs[i]->transform_component(id[i], t);
    }
}

void Actor::init( const ActorResource* resource, const hkQsTransform& t, ActorId32 id)
{
    m_resource = resource;
#ifdef HAVOK_COMPILE
    m_transform.setIdentity();
#endif
    m_values = 0;
    m_id = id;
    uint32_t num = resource->m_numComponents;
    ComponentFactory** facs = resource->m_factories;

    for (uint32_t i=0; i<num; ++i)
    {
        const void* res = resource->m_resources[i];
        if(res) m_components[i] = facs[i]->create_component(res, id);
    }

    const Fact& fact = m_resource->m_fact;
    if(fact.m_value_size)
    {
        m_values = COMMON_ALLOC(char, fact.m_value_size);
        memcpy(m_values, fact.m_values, fact.m_value_size);
    }

    set_transform(t);
}

void Actor::destroy()
{
    uint32_t num = m_resource->m_numComponents;
    ComponentFactory** facs = m_resource->m_factories;
    Id* comps = m_components;
    for (uint32_t i=0; i<num; ++i)
    {
        facs[i]->destroy_component(comps[i]);
    }
    COMMON_DEALLOC(m_values);
}

void* Actor::get_first_component_of( const StringId& type )
{
    int index = get_first_component_index_of(type);
    if(index < 0) return NULL;
    return m_resource->m_factories[index]->get_component(m_components[index]);
}

int Actor::get_first_component_index_of(const StringId& type)
{
    const ActorResource* res = m_resource;
    uint32_t num = res->m_numComponents;
    StringId* types = res->m_resourceTypes;
    for (uint32_t i=0; i<num; ++i)
    {
        if(types[i] == type)
            return i;
    }
    return -1;
}

uint32_t Actor::get_components_of( const StringId& type, void** comps, uint32_t buflen )
{
    uint32_t ret = 0;
    const ActorResource* res = m_resource;
    uint32_t num = res->m_numComponents;
    StringId* types = res->m_resourceTypes;
    for (uint32_t i=0; i<num; ++i)
    {
        if(types[i] == type)
        {
            Id id = m_components[i];
            ComponentFactory* fac = res->m_factories[i];
            comps[ret++] = fac->get_component(id);
            if(ret >= buflen)
                return ret;
        }
    }
    return ret;
}

uint32_t Actor::get_component_indices_of( const StringId& type, int* indices, uint32_t buflen )
{
    uint32_t ret = 0;
    const ActorResource* res = m_resource;
    uint32_t num = res->m_numComponents;
    StringId* types = res->m_resourceTypes;
    for (uint32_t i=0; i<num; ++i)
    {
        if(types[i] == type)
        {
            indices[ret++] = buflen;
            if(ret >= buflen)
                return ret;
        }
    }
    return ret;
}

bool Actor::has_key(const StringId& k) const
{
    return m_resource->m_fact.has_key(k);
}

uint32_t Actor::value_type(const StringId& k)
{
    return m_resource->m_fact.value_type(k);
}

bool Actor::get_key(const StringId& k, int& v) const
{
    return m_resource->m_fact.get_key(m_values, k, v);
}

bool Actor::get_key(const StringId& k, float& v) const
{
    return m_resource->m_fact.get_key(m_values, k, v);
}

bool Actor::get_key(const StringId& k, StringId& v) const
{
    return m_resource->m_fact.get_key(m_values, k, v);
}

bool Actor::get_key(const StringId& k, float* v) const
{
    return m_resource->m_fact.get_key(m_values, k, v);
}

bool Actor::set_key(const StringId& k, int v)
{
    return m_resource->m_fact.set_key(m_values, k, v);
}

bool Actor::set_key(const StringId& k, float v)
{
    return m_resource->m_fact.set_key(m_values, k, v);
}

bool Actor::set_key(const StringId& k, const StringId& v)
{
    return m_resource->m_fact.set_key(m_values, k, v);
}

bool Actor::set_key(const StringId& k, const float* v)
{
    return m_resource->m_fact.set_key(m_values, k, v);
}




ActorWorld g_actorWorld;
typedef IdArray<Actor> ActorBucket;
static ActorBucket g_actorBuckets[kActorClassNum];

void ActorWorld::init()
{
    g_actorBuckets[kLevelGeometry].init(MAX_LEVEL_GEOMETRY, &default_allocator());
    g_actorBuckets[kProp].init(MAX_PROP, &default_allocator());
    g_actorBuckets[kCharacter].init(MAX_CHARACTER, &default_allocator());
    m_shading_env = 0;
}


void ActorWorld::destroy()
{
    clear();
    for(uint32_t i=0; i<kActorClassNum; ++i)
    {
        g_actorBuckets[i].destroy();
    }
}

void ActorWorld::clear()
{
    for(uint32_t i=0; i<kActorClassNum; ++i)
    {
        clear_actors(i);
    }
}

void ActorWorld::clear_actors(Actor* actors, uint32_t num)
{
    for (uint32_t i = 0; i < num; ++i)
    {
        actors[i].destroy();
    }
}

void ActorWorld::clear_actors(uint32_t type)
{
    clear_actors(g_actorBuckets[type].begin(), g_actorBuckets[type].size());
}

ActorId32 ActorWorld::create_actor( const void* res , const hkQsTransform& t)
{
    const ActorResource* actorResource = (const ActorResource*)res;
    if(!actorResource) return INVALID_U32;

    uint32_t classId = actorResource->m_class;
    Actor* actor;
    Id indexId = g_actorBuckets[classId].create(&actor);
    ActorId32 ret = ActorId::pack_actor_id(classId, indexId);
    actor->init(actorResource, t, ret);
    return ret;
}

ActorId32 ActorWorld::create_actor( const StringId& resourceName, const hkQsTransform& t )
{
    return create_actor(FIND_RESOURCE(ActorResource, resourceName), t);
}

void ActorWorld::destroy_actor( ActorId32 actor_id )
{
    if(actor_id == INVALID_U32) return;
    uint32_t classId;
    Id indexId;
    ActorId::unpack_actor_id(actor_id, classId, indexId);
    ActorBucket& bucket = g_actorBuckets[classId];
    if(!bucket.has(indexId)) return;
    bucket.get(indexId)->destroy();
    bucket.destroy(indexId);
}

Actor* ActorWorld::get_actor( ActorId32 actor_id )
{
    if(actor_id == INVALID_U32) return 0;
    uint32_t classId;
    Id indexId;
    ActorId::unpack_actor_id(actor_id, classId, indexId);
    ActorBucket& bucket = g_actorBuckets[classId];
    if(!bucket.has(indexId)) return 0;
    return bucket.get(indexId);
}

uint32_t ActorWorld::num_actors( uint32_t type )
{
    return g_actorBuckets[type].size();
}

Actor* ActorWorld::get_actors( uint32_t type )
{
    return g_actorBuckets[type].begin();
}

void ActorWorld::pre_step( float dt )
{
    g_animMgr.update_animations(dt);
    g_animMgr.update_attachment(g_actorBuckets[kCharacter].begin(), g_actorBuckets[kCharacter].size());
    g_physicsWorld.update_character_proxies(dt);
}

void ActorWorld::step( float dt )
{
    //g_moveMgr.move_characters(g_actorBuckets[kCharacter].begin(), g_actorBuckets[kCharacter].size(), dt);
    Graphics::update(m_shading_env, dt);
}

void ActorWorld::post_step( float dt )
{
    g_physicsWorld.sync_rigidbody_actors(g_actorBuckets[kProp].begin(), g_actorBuckets[kProp].size());
    g_physicsWorld.sync_proxy_actors(g_actorBuckets[kCharacter].begin(), g_actorBuckets[kCharacter].size());
}

void ActorWorld::draw()
{
    g_animMgr.skin_actors(g_actorBuckets[kCharacter].begin(), g_actorBuckets[kCharacter].size());
    Graphics::draw(m_shading_env);
}



