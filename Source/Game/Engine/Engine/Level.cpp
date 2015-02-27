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

void lookup_resource_level(void* resource)
{
    Level* l = (Level*)resource;
    uint32_t num = l->m_num_resources;
    LevelActorResource* resources = (LevelActorResource*)((char*)resource + l->m_resource_offset);
    for (uint32_t i = 0; i < num; ++i)
    {
        resources[i].m_resource = FIND_RESOURCE(ActorResource, EngineTypes::ACTOR, resources[i].m_name);
    }
}


void start_level(Level* l)
{
    hkQsTransform t;
    uint32_t num = l->m_num_objects;
    LevelObject* objects = (LevelObject*)((char*)resource + l->m_object_offset);
    LevelActorResource* resources = (LevelActorResource*)((char*)resource + l->m_resource_offset);
    for (uint32_t i = 0; i < num; ++i)
    {
        LevelObject& object = objects[i];
        transform_object(t, object.m_translation, object.m_rotation, object.m_scale);
        object.m_actorId = g_actorWorld.create_actor(resources[object.m_resource_index].m_resource, t);
    }
}

void stop_level(Level*)
{
    uint32_t num = l->m_num_objects;
    LevelObject* objects = (LevelObject*)((char*)resource + l->m_object_offset);
    for (uint32_t i = 0; i < num; ++i)
    {
        g_actorWorld.destroy_actor(objects[i].m_actorId);
    }
}