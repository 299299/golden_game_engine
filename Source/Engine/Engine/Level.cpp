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

void Level::load(uint32_t max_num_perframe)
{
    m_loadedObjects = 0;
    m_loadNumPerframe = max_num_perframe;
    m_state = kLevelStateLoadingObjects;
}

void Level::unload()
{
    for (uint32_t i=0; i<m_loadedObjects; ++i)
    {
        g_actorWorld.destroy_actor(m_objects[i].m_actorId);
    }
    m_loadedObjects = 0;
    m_state = kLevelStateUnloaded;
}

void Level::lookup()
{
    for (uint32_t i = 0; i < m_numResources; ++i)
    {
        m_resources[i].m_resource = FIND_RESOURCE(ActorResource, m_resources[i].m_name);
    }
}

void Level::update()
{
    if(m_state == kLevelStateLoadingObjects)
    {
        uint32_t numLeft = m_numObject - m_loadedObjects;
        uint32_t spawnThisFrame = numLeft > m_loadNumPerframe ? m_loadNumPerframe : numLeft;
        hkQsTransform t;
        for (uint32_t i = m_loadedObjects; i < m_loadedObjects + spawnThisFrame; ++i)
        {
            LevelObject& object = m_objects[i];
            transform_object(t, object.m_translation, object.m_rotation, object.m_scale);
            object.m_actorId = g_actorWorld.create_actor(m_resources[object.m_resourceIndex].m_resource, t);
        }

        m_loadedObjects += numLeft;
        if(m_loadedObjects == m_numObject)
            m_state = kLevelStateReady;
    }
}

void Level::flush()
{
    hkQsTransform t;
    for (uint32_t i = 0; i < m_numObject; ++i)
    {
        LevelObject& object = m_objects[i];
        transform_object(t, object.m_translation, object.m_rotation, object.m_scale);
        object.m_actorId = g_actorWorld.create_actor(m_resources[object.m_resourceIndex].m_resource, t);
    }
    m_loadedObjects = m_numObject;
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