#pragma once
#include "StringId.h"
#include "GameConfig.h"

class hkQsTransformf;

struct ComponentData
{
    StringId        m_type;
    uint32_t        m_index;
    uint32_t        m_size;
    uint32_t        m_offset;
};

typedef Id      (*func_create_component_t)(const void*, ActorId32);
typedef void    (*func_destroy_component_t)(Id);
typedef void*   (*func_get_component_t)(Id);
typedef int     (*func_num_components_t)();
typedef void*   (*func_get_components_t)();
typedef void    (*func_transform_component_t)(Id, const hkQsTransformf&);
typedef void    (*func_lookup_component_data_t)(void*);

struct ComponentFactory
{
    func_create_component_t       m_create_component;
    func_destroy_component_t      m_destroy_component;
    func_get_component_t          m_get_component;
    func_num_components_t         m_num_conmponents;
    func_get_components_t         m_get_components;
    func_transform_component_t    m_transform_component;
    func_lookup_component_data_t  m_lookup_component_data;
    int                           m_order;

    Id create_component(const void* res, ActorId32 id)
    {
        return m_create_component(res, id);
    }
    void  destroy_component(Id id)
    {
        m_destroy_component(id);
    }
    void transform_component(Id id, const hkQsTransformf& t)
    {
        if(m_transform_component)
            m_transform_component(id, t);
    }
    void* get_component(Id id)
    {
        return m_get_component(id);
    }
    uint32_t num_components()
    {
        return m_num_conmponents();
    }
    void* get_components()
    {
        return m_get_components();
    }
    void lookup_component_data(void* data)
    {
        if(m_lookup_component_data)
            m_lookup_component_data(data);
    }
};


struct ComponentManager
{
    void init();
    void shutdown();

    ComponentFactory* find_factory(StringId type);
    int find_factory_index(StringId type);
    ComponentFactory* get_factory(uint32_t index);
    void register_factory(const ComponentFactory& fac, StringId type);

    ComponentFactory         m_factories[MAX_COMPONENT_TYPES];
    StringId                 m_types[MAX_COMPONENT_TYPES];
    uint32_t                 m_num_types;
};


extern ComponentManager g_componentMgr;