#pragma once
#include "StringId.h"

struct LevelObject
{
    float               m_translation[3];
    float               m_rotation[4];
    float               m_scale[3];
    ActorId32           m_actor;
    StringId            m_name;
    int                 m_resource_index;
};

struct LevelActorResource
{
    StringId            m_name;
    void*               m_resource;
};

struct Level
{
    uint32_t            m_num_objects;
    uint32_t            m_num_resources;
    uint32_t            m_object_offset;
    uint32_t            m_resource_offset;
};

void   lookup_resource_level(void*);
void   start_level(Level*);
void   stop_level(Level*);