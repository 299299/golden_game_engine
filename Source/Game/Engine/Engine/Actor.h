#pragma once
#include "StringId.h"
#include "Prerequisites.h"
#include "Utils.h"

struct ShadingEnviroment;
struct ComponentFactory;

ENGINE_NATIVE_ALIGN struct ActorResource
{
    DECLARE_RESOURCE(actor);
    StringId*           m_resourceNames;
    StringId*           m_resourceTypes;
    ComponentFactory**  m_factories;
    void**              m_resources;
    uint32_t            m_numComponents;
    uint32_t            m_class;
    Fact                m_fact;
};

ENGINE_NATIVE_ALIGN struct Actor
{
    hkQsTransform               m_transform;
    Id                          m_components[16]; //-> hack!
    const ActorResource*        m_resource;
    char*                       m_values;
    ActorId32                   m_id;

    void    init(const ActorResource* resource, const hkQsTransform& t, ActorId32 id);
    void    destroy();
    void    set_transform(const hkQsTransform& t);
    void    set_transform_ignore_type(const hkQsTransform& t, const StringId& type);
    void*   get_first_component_of(const StringId& type);
    int     get_first_component_index_of(const StringId& type);
    uint32_t    get_components_of(const StringId& type, void** comps, uint32_t buflen);
    uint32_t    get_component_indices_of(const StringId& type, int* indices, uint32_t buflen);

    bool    has_key(const StringId& k) const;
    uint32_t value_type(const StringId& k);
    bool    get_key(const StringId& k, int& v) const;
    bool    get_key(const StringId& k, float& v) const;
    bool    get_key(const StringId& k, StringId& v) const;
    bool    get_key(const StringId& k, float* v) const;
    bool    set_key(const StringId& k, int v);
    bool    set_key(const StringId& k, float v);
    bool    set_key(const StringId& k, const StringId& v);
    bool    set_key(const StringId& k, const float* v);
};

struct ActorConfig
{
    int max_geometries;
    int max_props;
    int max_characters;
};

struct ActorWorld
{
    void        init(const ActorConfig& cfg);
    void        shutdown();

    void        clear();
    void        clear_actors(uint32_t type);
    
    ActorId32   create_actor(const StringId& resourceName, const hkQsTransform& t);
    ActorId32   create_actor(const void* actorResource, const hkQsTransform& t);
    void        destroy_actor(ActorId32 id);
    Actor*      get_actor(ActorId32 id);
    uint32_t    num_actors(uint32_t type);
    Actor*      get_actors(uint32_t type);

    void        pre_step(float dt);
    void        step(float dt);
    void        post_step(float dt);

    void        draw();

    ShadingEnviroment*      m_shading_env;

private:
    void        clear_actors(Actor* actors, uint32_t num);
};

extern ActorWorld g_actorWorld;