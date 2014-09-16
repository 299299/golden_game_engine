#pragma once
#include "config.h"
#include "BaseTypes.h"
#include "StringId.h"
#include "DataDef.h"

struct ActorResource
{
    StringId        m_componentResourceNames[kComponentTypeNum];
    void*           m_componentResources[kComponentTypeNum];
};


struct Actor
{
    Id              m_components[kComponentTypeNum];
};


struct ActorWorld
{
    
};