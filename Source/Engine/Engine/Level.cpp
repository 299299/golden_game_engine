#include "Level.h"
#include "Resource.h"
#include "MathDefs.h"
#include "Actor.h"
#include "Log.h"
#include "EngineAssert.h"

void transform_object(hkQsTransform& m, const float* t, const float* r, const float* s)
{
    m.setIdentity();
    transform_vec3(m.m_translation, t);
    transform_vec3(m.m_scale, s);
    m.m_rotation.set(r[0], r[1], r[2], r[3]);
    ENGINE_ASSERT(m.isOk(), "m should ok!");
}

void Level::load()
{
    if(m_numLoadedObjects >= m_numObject) return;
    hkQsTransform t;
    for (uint32_t i = 0; i < m_numObject; ++i)
    {
        LevelObject& object = m_objects[i];
        transform_object(t, object.m_translation, object.m_rotation, object.m_scale);
        object.m_actorId = g_actorWorld.create_actor(m_resources[object.m_resourceIndex].m_resource, t);
    }
    m_numLoadedObjects = m_numObject;
}

void Level::unload()
{
    for (uint32_t i=0; i<m_numObject; ++i)
    {
        g_actorWorld.destroy_actor(m_objects[i].m_actorId);
    }
}

void Level::lookup()
{
    for (uint32_t i = 0; i < m_numResources; ++i)
    {
        m_resources[i].m_resource = FIND_RESOURCE(ActorResource, m_resources[i].m_name);
    }
}

void*  load_resource_level(const char* data, uint32_t size)
{
    Level* level = (Level*)data;
    level->m_objects = (LevelObject*)(data + level->m_objectOffset);
    level->m_resources = (LevelActorResource*)(data + level->m_resourceOffset);
    return level;
}

void   lookup_resource_level(void* resource)
{
    Level* level = (Level*)resource;
    level->lookup();
}