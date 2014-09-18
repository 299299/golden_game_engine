#include "Actor.h"
#include "config.h"
#include "id_array.h"
#include "Resource.h"
#include "Model.h"
#include "Light.h"
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "MemorySystem.h"
#include "memory.h"

bool ActorResource::has_key(const StringId& k) const
{
    for (uint32_t i = 0; i < m_numKeys; ++i)
    {
        if(m_keys[i].name == k) return true;
    }
    return false;
}

bool ActorResource::get_key(const StringId& k, Key& out_k) const
{
    for (uint32_t i = 0; i < m_numKeys; ++i)
    {
        if(m_keys[i].name == k)
        {
            out_k = m_keys[i];
            return true;
        }
    }
    return false;
}

void* load_resource_actor(const char* data, uint32_t size)
{
    ActorResource* actor = (ActorResource*)data;
    char* p = (char*)data;
    p += sizeof(ActorResource);
    actor->m_keys = (Key*)(p);
    p += sizeof(actor->m_numKeys * sizeof(Key));
    actor->m_values = p;
    return actor;
}

void lookup_resource_actor(void* resource)
{
    extern StringId g_componentTypes[];
    ActorResource* actor = (ActorResource*)resource;
    for (uint32_t i=0; i<kComponentTypeNum; ++i)
    {
        StringId name = actor->m_resourceNames[i];
        actor->m_resources[i] = name.isZero() ? 0 : g_resourceMgr.findResource(g_componentTypes[i], name);
    }
}

void Actor::teleport_transform( const hkQsTransform& t )
{
    m_transform = t;
    transform_renders(t);
}

void Actor::init( const ActorResource* resource, const hkQsTransform& t)
{
    extern Id create_componet(uint32_t type, const void* resource);

    m_resource = resource;
    for (uint32_t i=0; i<kComponentTypeNum; ++i)
    {
        const void* res = resource->m_resources[i];
        if(res) m_components[i] = create_componet(i, res);
    }
    m_values = COMMON_ALLOC(char, m_resource->m_valueSize);
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
    return m_resource->has_key(k);
}

uint32_t Actor::value_type(const StringId& k)
{
    Key key;
    m_resource->get_key(k, key);
    return (ValueType::Enum) key.type;
}

bool Actor::get_key(const StringId& k, int& v) const
{
    Key key;
    bool has = m_resource->get_key(k, key);
    v = *(int*)(m_values + key.offset);
    return has;
}

bool Actor::get_key(const StringId& k, float& v) const
{
    Key key;
    bool has = m_resource->get_key(k, key);
    v = *(float*)(m_values + key.offset);
    return has;
}

bool Actor::get_key(const StringId& k, StringId& v) const
{
    Key key;
    bool has = m_resource->get_key(k, key);
    v = *(StringId*)(m_values + key.offset);
    return has;
}

bool Actor::get_key(const StringId& k, float* v) const
{
    Key key;
    bool has = m_resource->get_key(k, key);
    memcpy(v, m_values + key.offset, sizeof(float)*4);
    return has;
}

void Actor::set_key(const StringId& k, int v)
{
    Key key;
    if(!m_resource->get_key(k, key)) return;
    *(int*)(m_values + key.offset) = v;
}

void Actor::set_key(const StringId& k, float v)
{
    Key key;
    if(!m_resource->get_key(k, key)) return;
    *(float*)(m_values + key.offset) = v;
}

void Actor::set_key(const StringId& k, const StringId& v)
{
    Key key;
    if(!m_resource->get_key(k, key)) return;
    *(StringId*)(m_values + key.offset) = v;
}

void Actor::set_key(const StringId& k, const float* v)
{
    Key key;
    if(!m_resource->get_key(k, key)) return;
    memcpy(m_values + key.offset, v, sizeof(float) * 4);
}

ActorWorld g_actorWorld;
static DynamicIdArray<Actor> g_actorBuckets[kActorClassNum];

void ActorWorld::init()
{
    g_actorBuckets[kLevelGeometry].init(MAX_LEVEL_GEOMETRY, default_allocator());
    g_actorBuckets[kProp].init(MAX_PROP, default_allocator());
    g_actorBuckets[kCharacter].init(MAX_CHARACTER, default_allocator());
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
        clear_actors(g_actorBuckets[i].begin(), g_actorBuckets[i].size());
    }
}

void ActorWorld::clear_actors(Actor* actors, uint32_t num)
{
    for (uint32_t i = 0; i < num; ++i)
    {
        actors[i].destroy();
    }
}

ActorId ActorWorld::create_actor( const void* res , const hkQsTransform& t)
{
    const ActorResource* actorResource = (const ActorResource*)res;
    ActorId id;
    id.m_class = actorResource->m_class;
    Actor actor;
    actor.init(actorResource, t);
    id.m_id = g_actorBuckets[id.m_class].create(actor);
    return id;
}

ActorId ActorWorld::create_actor( const StringId& resourceName, const hkQsTransform& t )
{
    return create_actor(FIND_RESOURCE(ActorResource, resourceName), t);
}

void ActorWorld::destroy_actor( ActorId actorId )
{
    uint32_t classId = actorId.m_class;
    Id id = actorId.m_id;
    g_actorBuckets[classId].destroy(id);
}

Actor* ActorWorld::get_actor( ActorId id )
{
    if(!g_actorBuckets[id.m_class].has(id.m_id)) return 0;
    return &g_actorBuckets[id.m_class].get(id.m_id);
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

}

void ActorWorld::step( float dt )
{

}

void ActorWorld::post_step( float dt )
{
    g_physicsWorld.sync_actors(g_actorBuckets[kProp].begin(), g_actorBuckets[kProp].size());
}

void ActorWorld::draw()
{
    g_animMgr.skinActors(g_actorBuckets[kCharacter].begin(), g_actorBuckets[kCharacter].size());
}


