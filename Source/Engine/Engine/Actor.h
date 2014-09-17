#pragma once
#include "StringId.h"
#include "DataDef.h"
#include "Prerequisites.h"


struct ValueType
{
    enum Enum
    {
        INT,
        FLOAT,
        STRING,
        FLOAT4
    };
};

struct Key
{
    StringId    name;
    uint32_t    type;
    uint32_t    offset;
};

ENGINE_NATIVE_ALIGN struct ActorResource
{
    DECLARE_RESOURCE(actor);
    StringId        m_resourceNames[kComponentTypeNum];
    void*           m_resources[kComponentTypeNum];
    uint32_t        m_class;
    Key*            m_keys;
    uint32_t        m_numKeys;
    char*           m_values;
    uint32_t        m_numValues;
    uint32_t        m_valueSize;
    bool has_key(const StringId& k) const;
    bool get_key(const StringId& k, Key& out_k) const;
};

ENGINE_NATIVE_ALIGN struct Actor
{
    hkQsTransform           m_transform;
    Id                      m_components[kComponentTypeNum];
    const ActorResource*    m_resource;
    StringId                m_resourceName;
    char*                   m_values;

    void    init(const ActorResource* resource);
    void    destroy();
    void    teleport_transform(const hkQsTransform& t);
    void    transform_renders(const hkQsTransform& t);
    void*   get_component(uint32_t type);

    bool    has_key(const StringId& k) const;
    uint32_t value_type(const StringId& k);
    bool    get_key(const StringId& k, int& v) const;
    bool    get_key(const StringId& k, float& v) const;
    bool    get_key(const StringId& k, StringId& v) const;
    bool    get_key(const StringId& k, float* v) const;
    void    set_key(const StringId& k, int v);
    void    set_key(const StringId& k, float v);
    void    set_key(const StringId& k, const StringId& v);
    void    set_key(const StringId& k, const float* v);
};


struct ActorId
{
    Id              m_id;
    uint32_t        m_class;
};

struct ActorWorld
{
    void        clear();
    void        clear_actors(Actor* actors, uint32_t num);
    ActorId     create_actor(const void* actorResource, const hkQsTransform& t);
    void        destroy_actor(ActorId id);
    Actor*      get_actor(ActorId id);
    uint32_t    num_actors(uint32_t type);
    Actor*      get_actors(uint32_t type);

    void        frame_start(float dt);
    void        pre_step(float dt);
    void        step(float dt);
    void        post_step(float dt);

    void        draw();
};

extern ActorWorld g_actorWorld;