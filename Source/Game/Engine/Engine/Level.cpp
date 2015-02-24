#include "Level.h"
#include "Resource.h"
#include "MathDefs.h"
#include "Log.h"
#include "Actor.h"
#include "DataDef.h"

void transform_object(hkQsTransform& m, const float* t, const float* r, const float* s)
{
#ifdef HAVOK_COMPILE
    m.setIdentity();
    transform_vec3(m.m_translation, t);
    transform_vec3(m.m_scale, s);
    m.m_rotation.set(r[0], r[1], r[2], r[3]);
    ENGINE_ASSERT(m.isOk(), "m should ok!");
#endif
}

void Level::load()
{
    if(m_numLoadedObjects >= m_numObject) return;
    hkQsTransform t;
    uint32_t num = m_numObject;
    LevelObject* head = m_objects;
    for (uint32_t i = 0; i < num; ++i)
    {
        LevelObject& object = head[i];
        transform_object(t, object.m_translation, object.m_rotation, object.m_scale);
        object.m_actorId = g_actorWorld.create_actor(m_resources[object.m_resourceIndex].m_resource, t);
    }
    m_numLoadedObjects = m_numObject;
}

void Level::unload()
{
    uint32_t num = m_numObject;
    LevelObject* head = m_objects;
    for (uint32_t i=0; i<num; ++i)
    {
        g_actorWorld.destroy_actor(head[i].m_actorId);
    }
    m_numLoadedObjects = 0;
}

void Level::lookup()
{
    uint32_t num = m_numResources;
    LevelActorResource* head = m_resources;
    for (uint32_t i = 0; i < num; ++i)
    {
        head[i].m_resource = FIND_RESOURCE(ActorResource, EngineTypes::ACTOR, head[i].m_name);
    }
}

void*  load_resource_level(void* data, uint32_t size)
{
    Level* level = (Level*)data;
    level->m_objects = (LevelObject*)((char*)data + level->m_objectOffset);
    level->m_resources = (LevelActorResource*)((char*)data + level->m_resourceOffset);
    return level;
}

void   lookup_resource_level(void* resource)
{
    Level* level = (Level*)resource;
    level->lookup();
}