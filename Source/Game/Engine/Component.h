#pragma once
#include "StringId.h"
#include "GameConfig.h"

typedef Id      (*func_create_component)(const void*, ActorId32);
typedef void    (*func_destroy_component)(Id);
typedef void*   (*func_get_component)(Id);
typedef uint32_t(*func_num_components)();
typedef void*   (*func_get_components)();

struct ComponentFactory
{
    func_create_component       m_create_component;
    func_destroy_component      m_destroy_component;
    func_get_component          m_get_component;
    func_num_components         m_num_conmponents;
    func_get_components         m_get_components;

    Id create_component(const void* res, ActorId32 id)
    {
        return m_create_component(res, id);
    }
    void  destroy_component(Id id)
    {
        m_destroy_component(id);
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
};


struct ComponentManager
{
    void init();
    void shutdown();

    ComponentFactory* find_factory(const StringId& type);
    void register_factory(const ComponentFactory& fac, const StringId& type);

    ComponentFactory         m_factories[MAX_COMPONENT_TYPES];
    StringId                 m_types[MAX_COMPONENT_TYPES];
    uint32_t                 m_num_types;
};


extern ComponentManager g_componentMgr;