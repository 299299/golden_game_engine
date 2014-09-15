#pragma once
#include "StringId.h"

enum LevelState
{
    kLevelStateLoadingObjects = 0,
    kLevelStateLoadingModels,
    kLevelStateLoadingLights,
    kLevelStateReady,
    kLevelStateUnloaded,
    kLevelStateMax
};

struct EntityResource;
struct LevelObject
{
    float           m_translation[3];
    float           m_rotation[4];
    float           m_scale[3];
    uint32_t        m_entityId;
    StringId        m_name;
    int             m_resourceIndex;
};
struct LevelEntityResource
{
    StringId            m_name;
    EntityResource*     m_resource;
};
struct LevelModel
{
    float               m_translation[3];
    float               m_rotation[4];
    float               m_scale[3];
    void*               m_resource;
    StringId            m_modelName;
    uint32_t            m_modelId;
};
struct LevelLight
{
    float               m_translation[3];
    float               m_rotation[4];
    void*               m_resource;
    StringId            m_lightName;
    uint32_t            m_lightId;
};

ENGINE_NATIVE_ALIGN struct Level
{
    DECLARE_RESOURCE(level);

    //========================================================
    // hot data.
    uint32_t                    m_state;
    uint32_t                    m_loadedObjects;
    uint32_t                    m_loadNumPerframe;
    uint32_t                    m_loadedModels;

    //=============================================================
    // cold data
    LevelObject*                m_objects;
    LevelEntityResource*        m_resources;
    LevelModel*                 m_models;
    LevelLight*                 m_lights;

    uint32_t                    m_numObject;
    uint32_t                    m_numResources;
    uint32_t                    m_numModels;
    uint32_t                    m_numLights;

    uint32_t                    m_objectOffset;
    uint32_t                    m_resourceOffset;
    uint32_t                    m_modelOffset;
    uint32_t                    m_lightOffset;

    void  lookup();
    void  load(uint32_t max_num_perframe = 100);
    void  unload();
    void  update();
    void  flush();
    LevelObject* findObject(const StringId& name)  const;
};


