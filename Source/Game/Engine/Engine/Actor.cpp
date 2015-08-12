#include "Actor.h"
#include "Component.h"
#include "IdArray.h"
#include "Resource.h"
#include "Level.h"
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "MemorySystem.h"
#include "memory.h"
#include "Utils.h"
#include "DataDef.h"
#include "Graphics.h"

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

void lookup_resource_actor(void* resource)
{
    ActorResource* actor = (ActorResource*)resource;
    char* p = (char*)resource;
    ComponentData* comp_data = (ComponentData*)(p + actor->m_component_data_offset);
    uint32_t num = actor->m_num_components;
    for (uint32_t i=0; i<num; ++i)
    {
        ComponentData& data = comp_data[i];
        ComponentFactory* fac = g_componentMgr.get_factory(data.m_index);
        ENGINE_ASSERT(fac, "Can not find component factory %d", data.m_index);
        fac->lookup_component_data(p + data.m_offset);
    }
}

void Actor::set_transform( const hkQsTransform& t )
{
    m_transform = t;

    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_num_components;
    Id* id = m_components;
    ComponentData* data = (ComponentData*)((char*)resource + resource->m_component_data_offset);

    for (uint32_t i=0; i<num; ++i)
    {
        g_componentMgr.get_factory(data[i].m_index)->transform_component(id[i], t);
    }
}

void Actor::set_transform_ignore_type( const hkQsTransform& t, StringId type )
{
    m_transform = t;

    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_num_components;
    Id* id = m_components;
    ComponentData* data = (ComponentData*)((char*)resource + resource->m_component_data_offset);

    for (uint32_t i=0; i<num; ++i)
    {
        if(data[i].m_type == type)
            continue;
        g_componentMgr.get_factory(data[i].m_index)->transform_component(id[i], t);
    }
}

void Actor::init( void* resource, const hkQsTransform& t, ActorId32 id)
{
    m_resource = (const ActorResource*)resource;
#ifdef HAVOK_COMPILE
    m_transform.setIdentity();
#endif
    m_id = id;
    const ActorResource* actorResource = m_resource;

    Fact* fact = (Fact*)((char*)resource + actorResource->m_fact_offset);
    m_blob = COMMON_ALLOC(char, fact->m_value_size);
    fact->fill_default_values(m_blob);

    uint32_t num = actorResource->m_num_components;
    char* p = (char*)resource;
    ComponentData* data = (ComponentData*)(p + actorResource->m_component_data_offset);
    Id* ids = m_components;

    for (uint32_t i=0; i<num; ++i)
    {
        ComponentData* _d = data + i;
        char* _data = p + _d->m_offset;
        ComponentFactory* fac = g_componentMgr.get_factory(_d->m_index);
        ids[i] = fac->create_component(_data, m_id);
    }

    set_transform(t);
}

void Actor::destroy()
{
    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_num_components;
    ComponentData* data = (ComponentData*)((char*)resource + resource->m_component_data_offset);
    Id* comps = m_components;
    for (uint32_t i=0; i<num; ++i)
    {
        g_componentMgr.get_factory(data[i].m_index)->destroy_component(comps[i]);
    }

    COMMON_DEALLOC(m_blob);
}

void* Actor::get_first_component_of( StringId type )
{
    int index = get_first_component_index_of(type);
    if(index < 0) return NULL;
    const ActorResource* resource = m_resource;
    ComponentData* data = (ComponentData*)((char*)resource + resource->m_component_data_offset);
    return g_componentMgr.get_factory(data[index].m_index)->get_component(m_components[index]);
}

int Actor::get_first_component_index_of(StringId type)
{
    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_num_components;
    ComponentData* data = (ComponentData*)((char*)resource + resource->m_component_data_offset);
    for (uint32_t i=0; i<num; ++i)
    {
        if(data[i].m_type == type)
            return i;
    }
    return -1;
}

uint32_t Actor::get_components_of( StringId type, void** comps, uint32_t buflen )
{
    uint32_t ret = 0;
    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_num_components;
    ComponentData* data = (ComponentData*)((char*)resource + resource->m_component_data_offset);
    for (uint32_t i=0; i<num; ++i)
    {
        if(data[i].m_type == type)
        {
            Id id = m_components[i];
            ComponentFactory* fac = g_componentMgr.get_factory(data[i].m_index);
            comps[ret++] = fac->get_component(id);
            if(ret >= buflen)
                return ret;
        }
    }
    return ret;
}

uint32_t Actor::get_component_indices_of( StringId type, int* indices, uint32_t buflen )
{
    uint32_t ret = 0;
    const ActorResource* resource = m_resource;
    uint32_t num = resource->m_num_components;
    ComponentData* data = (ComponentData*)((char*)resource + resource->m_component_data_offset);
    for (uint32_t i=0; i<num; ++i)
    {
        if(data[i].m_type == type)
        {
            indices[ret++] = buflen;
            if(ret >= buflen)
                return ret;
        }
    }
    return ret;
}

ActorWorld g_actorWorld;
typedef IdArray<Actor> ActorBucket;
static ActorBucket g_actorBuckets[kActorClassNum];

void ActorWorld::init(const ActorConfig& cfg)
{
    g_actorBuckets[kLevelGeometry].init(cfg.max_geometries, &default_allocator());
    g_actorBuckets[kProp].init(cfg.max_props, &default_allocator());
    g_actorBuckets[kCharacter].init(cfg.max_characters, &default_allocator());
    m_shading_env = 0;
}


void ActorWorld::shutdown()
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

ActorId32 ActorWorld::create_actor( void* res , const hkQsTransform& t, StringId name)
{
    const ActorResource* actorResource = (const ActorResource*)res;
    if(!actorResource)
        return INVALID_U32;

    uint32_t classId = actorResource->m_class;
    Actor* actor;
    Id indexId = g_actorBuckets[classId].create(&actor);
    ActorId32 ret = ActorId::pack_actor_id(classId, indexId);
    actor->init(res, t, ret);
    actor->m_name = name;
    return ret;
}

ActorId32 ActorWorld::create_actor( StringId resourceName, const hkQsTransform& t, StringId name)
{
    return create_actor(FIND_RESOURCE(ActorResource, EngineTypes::ACTOR, resourceName), t, name);
}

void ActorWorld::destroy_actor( ActorId32 actor_id )
{
    if(actor_id == INVALID_U32)
        return;
    uint32_t classId;
    Id indexId;
    ActorId::unpack_actor_id(actor_id, classId, indexId);
    ActorBucket& bucket = g_actorBuckets[classId];
    if(!bucket.has(indexId))
        return;
    bucket.get(indexId)->destroy();
    bucket.destroy(indexId);
}

Actor* ActorWorld::get_actor( ActorId32 actor_id )
{
    if(actor_id == INVALID_U32)
        return 0;
    uint32_t classId;
    Id indexId;
    ActorId::unpack_actor_id(actor_id, classId, indexId);
    ActorBucket& bucket = g_actorBuckets[classId];
    if(!bucket.has(indexId))
        return 0;
    return bucket.get(indexId);
}

int ActorWorld::num_actors( int type )
{
    return g_actorBuckets[type].size();
}

Actor* ActorWorld::get_actors( int type )
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

void ActorWorld::register_factories()
{
    ResourceFactory _actor = {0, 0, lookup_resource_actor, 0, 0, EngineNames::ACTOR, 10};
    g_resourceMgr.register_factory(_actor);

    ResourceFactory _level = {0, 0, lookup_resource_level, 0, 0, EngineNames::LEVEL, 11};
    g_resourceMgr.register_factory(_level);
}

static ActorId32 _find_actor(const ActorBucket& bucket, StringId name)
{
    const Actor* _actors = bucket.begin();
    int _size = bucket.size();
    for (int i=0; i<_size; ++i) {
        if (_actors[i].m_name == name) {
            return _actors[i].m_id;
        }
    }
    return INVALID_U32;
}

ActorId32 ActorWorld::find_actor(StringId name, int type)
{
    if (type < 0) {
        for (int i=0; i<kActorClassNum; ++i) {
            ActorId32 ret = _find_actor(g_actorBuckets[i], name);
            if (ret != INVALID_U32)
                return ret;
        }
    }
    else {
        return _find_actor(g_actorBuckets[type], name);
    }
    return INVALID_U32;
}
