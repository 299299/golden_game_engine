#include "Level.h"
#include "EntityManager.h"
#include "Resource.h"
#include "MathDefs.h"
#include "Entity.h"
#include "Model.h"
#include "Light.h"
#include "Log.h"

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
    m_loadNumPerframe = max_num_perframe;
    m_loadedObjects = 0;
    m_loadedModels = 0;
    m_state = kLevelStateLoadingObjects;
    ComponentFactory* lightFactory = g_componentMgr.findFactory(LightResource::getType());
    for (uint32_t i=0; i<m_numLights; ++i)
    {
        m_lights[i].m_lightId = lightFactory->addComponent(m_lights[i].m_resource);
    }
}

void Level::unload()
{
    for (uint32_t i=0; i<m_loadedObjects; ++i)
    {
        g_entityMgr.removeInstance(m_objects[i].m_entityId);
    }
    ComponentFactory* modelFactory = g_componentMgr.findFactory(ModelResource::getType());
    for (uint32_t i=0; i<m_loadedModels; ++i)
    {
        modelFactory->removeComponent(m_models[i].m_modelId);
    }
    ComponentFactory* lightFactory = g_componentMgr.findFactory(LightResource::getType());
    for (uint32_t i=0; i<m_numLights; ++i)
    {
        lightFactory->removeComponent(m_lights[i].m_lightId);
    }
    m_loadedObjects = 0;
    m_loadedModels = 0;
    m_state = kLevelStateUnloaded;
}

void Level::lookup()
{
    for (uint32_t i = 0; i < m_numResources; ++i)
    {
        m_resources[i].m_resource = FIND_RESOURCE(EntityResource, m_resources[i].m_name);
    }
    for (uint32_t i = 0; i < m_numModels; ++i)
    {
        m_models[i].m_resource = FIND_RESOURCE(ModelResource, m_models[i].m_modelName);
    }
    for (uint32_t i = 0; i < m_numLights; ++i)
    {
        m_lights[i].m_resource = FIND_RESOURCE(LightResource, m_lights[i].m_lightName);
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
            object.m_entityId = g_entityMgr.addInstance(m_resources[object.m_resourceIndex].m_resource, t);
            //LOGI("create entity %d = %d", i, object.m_entityId);
        }

        m_loadedObjects += numLeft;
        if(m_loadedObjects == m_numObject)
            m_state = kLevelStateLoadingModels;
    }
    else if(m_state == kLevelStateLoadingModels)
    {
        uint32_t numLeft = m_numModels - m_loadedModels;
        uint32_t spawnThisFrame = numLeft > m_loadNumPerframe ? m_loadNumPerframe : numLeft;

        hkQsTransform t;
        t.setIdentity();

        ComponentFactory* modelFactory = g_componentMgr.findFactory(ModelResource::getType());
        for (uint32_t i = m_loadedModels; i < m_loadedModels + spawnThisFrame; ++i)
        {
            LevelModel& model = m_models[i];
            transform_object(t, model.m_translation, model.m_rotation, model.m_scale);
            model.m_modelId = modelFactory->addComponent(model.m_resource);
        }

        m_loadedModels += numLeft;
        if(m_loadedModels == m_numModels)
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
        object.m_entityId = g_entityMgr.addInstance(m_resources[object.m_resourceIndex].m_resource, t);
    }
    m_loadedObjects = m_numObject;
    ComponentFactory* modelFactory = g_componentMgr.findFactory(ModelResource::getType());
    for (uint32_t i = 0; i < m_numModels; ++i)
    {
        LevelModel& model = m_models[i];
        transform_object(t, model.m_translation, model.m_rotation, model.m_scale);
        model.m_modelId = modelFactory->addComponent(model.m_resource);
        modelFactory->transformComponent(model.m_modelId, t);
        //ModelInstance* modelInstance = (ModelInstance*)modelFactory->lookupComponent(model.m_modelId);
        //modelInstance->setTransform(t);
        //modelInstance->addFlag(kNodeNoShadow);
    }
    m_loadedModels = m_numModels;
}

LevelObject* Level::findObject( const StringId& name ) const
{
    for (uint32_t i=0; i<m_numObject; ++i)
    {
        if(m_objects[i].m_name == name)
            return &m_objects[i];
    }
    return 0;
}

void*  load_resource_level(const char* data, uint32_t size)
{
    Level* level = (Level*)data;
    level->m_objects = (LevelObject*)(data + level->m_objectOffset);
    level->m_resources = (LevelEntityResource*)(data + level->m_resourceOffset);
    level->m_models = (LevelModel*)(data + level->m_modelOffset);
    level->m_lights = (LevelLight*)(data + level->m_lightOffset);
    return level;
}

void   lookup_resource_level(void* resource)
{
    Level* level = (Level*)resource;
    level->lookup();
}