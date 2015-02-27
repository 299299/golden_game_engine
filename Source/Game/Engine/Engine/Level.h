#pragma once
#include "StringId.h"

struct LevelObject
{
    float               m_translation[3];
    float               m_rotation[4];
    float               m_scale[3];
    ActorId32           m_actorId;
    StringId            m_name;
    int                 m_resourceIndex;
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

struct Level
{
    uint32_t                    m_numLoadedObjects;
    // cold data
    LevelObject*                m_objects;
    LevelActorResource*         m_resources;

    uint32_t                    m_numObject;
    uint32_t                    m_numResources;

    uint32_t                    m_objectOffset;
    uint32_t                    m_resourceOffset;

    void  lookup();
    void  load();
    void  unload();
};


void*  load_resource_level(void*, uint32_t);
void   lookup_resource_level(void*);