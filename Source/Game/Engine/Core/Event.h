#pragma once
#include "BaseTypes.h"
#include "StringId.h"

struct CollisionEvent
{
    ActorId32                   m_objects[2];
    float                       m_normal[3];
    float                       m_position[3];
    float                       m_velocity;
};

struct AnimationEvent
{
    ActorId32                   m_who;
    StringId                    m_name;
    char                        m_padding[8];
};