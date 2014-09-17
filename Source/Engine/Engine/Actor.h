#pragma once
#include "StringId.h"
#include "DataDef.h"
#include "Prerequisites.h"

ENGINE_NATIVE_ALIGN struct ActorResource
{
    DECLARE_RESOURCE(actor);
    StringId        m_resourceNames[kComponentTypeNum];
    void*           m_resources[kComponentTypeNum];
    uint32_t        m_class;
};

ENGINE_NATIVE_ALIGN struct Actor
{
    hkQsTransform           m_transform;
    Id                      m_components[kComponentTypeNum];
    const ActorResource*    m_resource;
    StringId                m_resourceName;

    void    init(const ActorResource* resource);
    void    destroy();
    void    teleport_transform(const hkQsTransform& t);
    void    transform_renders(const hkQsTransform& t);
    void*   get_component(uint32_t type);
};


struct ActorId
{
    Id              m_id;
    uint32_t        m_class;
};

struct ActorWorld
{
    ActorId     create_actor(const void* actorResource, const hkQsTransform& t);
    void        destroy_actor(ActorId id);
    Actor*      get_actor(ActorId id);
    uint32_t    num_actors(uint32_t type);
    Actor*      get_actors(uint32_t type);

    void        pre_step(float dt);
    void        step(float dt);
    void        post_step(float dt);

    void        draw();
};

extern ActorWorld g_actorWorld;