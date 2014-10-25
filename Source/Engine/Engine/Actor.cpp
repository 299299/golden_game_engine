#include "Actor.h"
#include "config.h"
#include "id_array.h"
#include "Resource.h"
#include "Model.h"
#include "Light.h"
#include "Script.h"
#include "Graphics.h"
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "MemorySystem.h"
#include "memory.h"
#include "EngineAssert.h"

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
    Fact& fact = actor->m_fact;
    fact.m_keys = (Key*)(p);
    p += sizeof(actor->m_fact.m_num_keys * sizeof(Key));
    fact.m_values = p;
    return actor;
}


void lookup_resource_actor(void* resource)
{
    extern StringId g_componentTypes[];
    ActorResource* actor = (ActorResource*)resource;
    for (uint32_t i=0; i<kComponentTypeNum; ++i)
    {
        StringId name = actor->m_resourceNames[i];
        actor->m_resources[i] = name ? g_resourceMgr.find_resource(g_componentTypes[i], name) : 0;
    }
}

void Actor::teleport_transform( const hkQsTransform& t )
{
    m_transform = t;
    transform_renders(t);
}

void Actor::init( const ActorResource* resource, const hkQsTransform& t, ActorId32 id)
{
    extern Id create_componet(uint32_t, const void*, ActorId32);

    m_resource = resource;
    m_transform.setIdentity();
    m_values = 0;
    m_id = id;

    for (uint32_t i=0; i<kComponentTypeNum; ++i)
    {
        const void* res = resource->m_resources[i];
        if(res) m_components[i] = create_componet(i, res, id);
    }

    const Fact& fact = m_resource->m_fact;
    if(fact.m_value_size)
    {
        m_values = COMMON_ALLOC(char, fact.m_value_size);
        memcpy(m_values, fact.m_values, fact.m_value_size);
    }
    
    teleport_transform(t);
}

void Actor::destroy()
{
    extern void  destroy_component(uint32_t type, Id id);
    for (uint32_t i=0; i<kComponentTypeNum; ++i)
    {
        destroy_component(i, m_components[i]);
    }
    COMMON_DEALLOC(m_values);
}

void Actor::transform_renders( const hkQsTransform& t )
{
    extern void* get_render_model(Id);
    extern void* get_render_light(Id);

    m_transform = t;
    Id id = m_components[kComponentModel];
    ModelInstance* model = (ModelInstance*)get_render_model(id);
    if(model) 
    {
        transform_matrix(model->m_transform, t);
        ADD_BITS(model->m_flag, kNodeTransformDirty);
    }

    id = m_components[kComponentLight];
    LightInstance* light = (LightInstance*)get_render_light(id);
    if(light)
    {
        transform_matrix(light->m_transform, t);
        ADD_BITS(light->m_flag, kNodeTransformDirty);
    }
}

void* Actor::get_component( uint32_t type )
{
    extern void* get_component(uint32_t type, Id id);
    return get_component(type, m_components[type]);
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
typedef DynamicIdArray<Actor> ActorBucket;
static ActorBucket g_actorBuckets[kActorClassNum];

void ActorWorld::init()
{
    g_actorBuckets[kLevelGeometry].init(MAX_LEVEL_GEOMETRY, default_allocator());
    g_actorBuckets[kProp].init(MAX_PROP, default_allocator());
    g_actorBuckets[kCharacter].init(MAX_CHARACTER, default_allocator());
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
    Actor actor;
    Id indexId = g_actorBuckets[classId].create(actor);
    ActorId32 ret = ActorId::pack_actor_id(classId, indexId);
    g_actorBuckets[classId].get(indexId).init(actorResource, t, ret);
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
    bucket.get(indexId).destroy();
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
    return &bucket.get(indexId);
}

uint32_t ActorWorld::num_actors( uint32_t type )
{
    return g_actorBuckets[type].size();
}

Actor* ActorWorld::get_actors( uint32_t type )
{
    return g_actorBuckets[type].begin();
}

void ActorWorld::frame_start(float dt)
{
    
}

void ActorWorld::pre_step( float dt )
{
    g_animMgr.update_animations(dt);
	g_animMgr.apply_animation_rootmotion(g_actorBuckets[kCharacter].begin(), g_actorBuckets[kCharacter].size(), dt);
    g_physicsWorld.update_character_proxies(dt);
}

void ActorWorld::step( float dt )
{
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



