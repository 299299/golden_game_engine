#pragma once
#include "StringId.h"
#include "Prerequisites.h"
#include "Utils.h"
#include "GameConfig.h"

struct ShadingEnviroment;
struct ComponentFactory;
struct ComponentData;

ENGINE_NATIVE_ALIGN(struct) ActorResource
{
    uint32_t            m_component_data_offset;
    uint32_t            m_num_components;
    uint32_t            m_class;
};

ENGINE_NATIVE_ALIGN(struct) Actor
{
    hkQsTransform               m_transform;
    Id                          m_components[MAX_COMPONET_PER_ACTOR];
    const ActorResource*        m_resource;
    char*                       m_values;
    ActorId32                   m_id;

    void        init(void* resource, const hkQsTransform& t, ActorId32 id);
    void        destroy();
    void        set_transform(const hkQsTransform& t);
    void        set_transform_ignore_type(const hkQsTransform& t, StringId type);
    void*       get_first_component_of(StringId type);
    int         get_first_component_index_of(StringId type);
    uint32_t    get_components_of(StringId type, void** comps, uint32_t buflen);
    uint32_t    get_component_indices_of(StringId type, int* indices, uint32_t buflen);
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

    ActorId32   create_actor(StringId resourceName, const hkQsTransform& t);
    ActorId32   create_actor(void* actorResource, const hkQsTransform& t);
    void        destroy_actor(ActorId32 id);
    Actor*      get_actor(ActorId32 id);
    uint32_t    num_actors(uint32_t type);
    Actor*      get_actors(uint32_t type);

    void        pre_step(float dt);
    void        step(float dt);
    void        post_step(float dt);

    void        draw();

    ShadingEnviroment*      m_shading_env;

    static void register_factories();

private:
    void        clear_actors(Actor* actors, uint32_t num);
};

extern ActorWorld g_actorWorld;

void  lookup_resource_actor(void*);