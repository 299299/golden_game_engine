#pragma once
#include "StringId.h"
#include "Actor.h"

enum LevelState
{
    kLevelStateLoadingObjects = 0,
    kLevelStateReady,
    kLevelStateUnloaded,
    kLevelStateMax
};


struct LevelObject
{
    float           m_translation[3];
    float           m_rotation[4];
    float           m_scale[3];
    ActorId         m_actorId;
    StringId        m_name;
    int             m_resourceIndex;
};
struct LevelActorResource
{
    StringId            m_name;
    void*               m_resource;
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
    //=============================================================
    // cold data
    LevelObject*                m_objects;
    LevelActorResource*         m_resources;

    uint32_t                    m_numObject;
    uint32_t                    m_numResources;

    uint32_t                    m_objectOffset;
    uint32_t                    m_resourceOffset;

    void  lookup();
    void  load(uint32_t max_num_perframe = 100);
    void  unload();
    void  update();
    void  flush();
};


