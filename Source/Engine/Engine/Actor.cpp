#include "Actor.h"
#include "config.h"
#include "id_array.h"
#include "Resource.h"
#include "Model.h"
#include "Light.h"
#include "AnimationSystem.h"
#include "PhysicsWorld.h"

static IdArray<MAX_LEVEL_GEOMETRY, Actor>   g_levelGeometries;
static IdArray<MAX_PROP, Actor>             g_props;
static IdArray<kCharacter, Actor>           g_characters;

void* load_resource_actor(const char* data, uint32_t size)
{
    return (ActorResource*)data;
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

void Actor::init( const ActorResource* resource )
{
    extern Id create_componet(uint32_t type, const void* resource);

    m_resource = resource;
    for (uint32_t i=0; i<kComponentTypeNum; ++i)
    {
        const void* res = resource->m_resources[i];
        if(res) m_components[i] = create_componet(i, res);
    }
}

void Actor::destroy()
{
    extern void  destroy_component(uint32_t type, Id id);
    for (uint32_t i=0; i<kComponentTypeNum; ++i)
    {
        destroy_component(i, m_components[i]);
    }
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


ActorWorld g_actorWorld;

ActorId ActorWorld::create_actor( const void* res , const hkQsTransform& t)
{
    const ActorResource* actorResource = (const ActorResource*)res;
    ActorId id;
    id.m_class = actorResource->m_class;
    Actor actor;
    actor.init(actorResource);
    switch(id.m_class)
    {
    case kLevelGeometry:
        id.m_id = id_array::create(g_levelGeometries, actor);
        break;
    case kProp:
        id.m_id = id_array::create(g_props, actor);
        break;
    case kCharacter:
        id.m_id = id_array::create(g_characters, actor);
        break;
    default:
        return ActorId();
    }
    return id;
}

void ActorWorld::destroy_actor( ActorId actorId )
{
    uint32_t classId = actorId.m_class;
    Id id = actorId.m_id;
    switch(classId)
    {
    case kLevelGeometry:
        if(!id_array::has(g_levelGeometries, id)) return;
        id_array::get(g_levelGeometries, id).destroy();
        id_array::destroy(g_levelGeometries, id);
        break;
    case kProp:
        if(!id_array::has(g_props, id)) return;
        id_array::get(g_props, id).destroy();
        id_array::destroy(g_props, id);
        break;
    case kCharacter:
        if(!id_array::has(g_characters, id)) return;
        id_array::get(g_characters, id).destroy();
        id_array::destroy(g_characters, id);
        break;
    default:
        return;
    }
}

Actor* ActorWorld::get_actor( ActorId id )
{
    switch(id.m_class)
    {
    case kLevelGeometry:
        if(!id_array::has(g_levelGeometries, id.m_id)) return 0;
        return &id_array::get(g_levelGeometries, id.m_id);
        break;
    case kProp:
        if(!id_array::has(g_props, id.m_id)) return 0;
        return &id_array::get(g_props, id.m_id);
        break;
    case kCharacter:
        if(!id_array::has(g_characters, id.m_id)) return 0;
        return &id_array::get(g_characters, id.m_id);
        break;
    default:
        return 0;
    }
}

uint32_t ActorWorld::num_actors( uint32_t type )
{
    switch(type)
    {
    case kLevelGeometry: return id_array::size(g_levelGeometries);
    case kProp: return id_array::size(g_props);
    case kCharacter: return id_array::size(g_characters);
    default: return 0;
    }
}

Actor* ActorWorld::get_actors( uint32_t type )
{
    switch(type)
    {
    case kLevelGeometry: return id_array::begin(g_levelGeometries);
    case kProp: return id_array::begin(g_props);
    case kCharacter: return id_array::begin(g_characters);
    default: return 0;
    }
}

void ActorWorld::preStep( float dt )
{

}

void ActorWorld::update( float dt )
{

}

void ActorWorld::postStep( float dt )
{
    g_physicsWorld.sync_actors(id_array::begin(g_props), id_array::size(g_props));
}

void ActorWorld::draw()
{
    g_animMgr.skinActors(id_array::begin(g_characters), id_array::size(g_characters));
}


