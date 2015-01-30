#include "Component.h"


ComponentManager g_componentMgr;
void ComponentManager::init()
{
    m_num_types = 0;
}

void ComponentManager::shutdown()
{

}

ComponentFactory* ComponentManager::find_factory( StringId type )
{
    uint32_t num = m_num_types;
    StringId* types = m_types;
    for (uint32_t i=0; i<num; ++i)
    {
        if(types[i] == type)
            return &m_factories[i];
    }
    return NULL;
}

void ComponentManager::register_factory( const ComponentFactory& fac, StringId type )
{
    uint32_t num = m_num_types;
    ++m_num_types;
    m_types[num] = type;
    m_factories[num] = fac;
}
