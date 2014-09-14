#include "Entity.h"
#include "DataDef.h"
#include "Log.h"
#include "Resource.h"
#include "Memory.h"
#include "ComponentManager.h"

ComponentManager g_componentMgr;

void ComponentManager::init( uint32_t maxNum )
{
    m_factories = STATIC_ALLOC(ComponentFactory*, maxNum);
    m_types = STATIC_ALLOC(StringId, maxNum);
    m_maxNumFactories = maxNum;
}

void EntityResource::lookup()
{
    for(int i=0; i<m_numComps; ++i)
    {
        ComponentResource& resource = m_resources[i];
        resource.m_resource = g_resourceMgr.findResource(resource.m_type, resource.m_resourceName);
        resource.m_factory = g_componentMgr.findFactory(resource.m_type);
        HK_ASSERT(0, resource.m_factory);
    }
}

void EntityResource::dump()
{
    LOGI("dummping entity-resource ----------------->");
    LOGI("num-of-components = %d", m_numComps);
    for(uint32_t i=0; i<m_numComps;++i)
    {
        const ComponentResource& resource = m_resources[i];
        LOGI("comp type = %s, name = %s", stringid_lookup(resource.m_type), stringid_lookup(resource.m_resourceName));
    }
}

Variant* EntityResource::findVariant( const StringId& name ) const
{
    for (uint32_t i=0; i<m_numVariants; ++i)
    {
        if(m_variants[i].m_name == name)
            return &m_variants[i].m_variant;
    }
    return 0;
}

void* load_resource_entity( const char* data, uint32_t size )
{
    EntityResource* entity = (EntityResource*)data;
    entity->m_resources = (ComponentResource*)(data + entity->m_resourceOffset);
    entity->m_variants = (NamedVariant*)(data + entity->m_varentOffset);

#ifdef DUMP_RESOURCE
    entity->dump();
#endif
    return entity;
}

void lookup_resource_entity( void * resource )
{
    EntityResource* entity = (EntityResource*)resource;
    entity->lookup();
}


void EntityInstance::init( const void* resource )
{
    m_resource = (const EntityResource*)resource;
    m_numComps = m_resource->m_numComps;
    const ComponentResource* res = m_resource->m_resources;
    for (uint32_t i=0; i<m_numComps; ++i)
    {
        const ComponentResource& resource = res[i];
        m_comps[i] = resource.m_factory->addComponent(resource.m_resource);
        //LOGI("m_comps[%d] = %d", i, m_comps[i]);
    }
}

void EntityInstance::destroy()
{
    const ComponentResource* res = m_resource->m_resources;
    for (uint32_t i=0; i<m_numComps; ++i)
    {
        res[i].m_factory->removeComponent(m_comps[i]);
    }
}

ID EntityInstance::getFirstCompIdTypeOf( const StringId& type ) const
{
    const ComponentResource* res = m_resource->m_resources;
    for (uint32_t i=0; i<m_numComps; ++i)
    {
        if(res[i].m_type == type)
            return m_comps[i];
    }
    return INVALID_ID;
}

uint32_t EntityInstance::getCompIdTypeOf( const StringId& type, ID* outIDs ) const
{
    uint32_t ret = 0;
    const ComponentResource* res = m_resource->m_resources;
    for (uint32_t i=0; i<m_numComps; ++i)
    {
        if(res[i].m_type == type)
            outIDs[ret++] = m_comps[i];
    }
    return INVALID_ID;
}

void* EntityInstance::getFirstCompTypeOf(const StringId& type) const
{
    return getComponent(getFirstCompIndexTypeOf(type));
}

uint32_t EntityInstance::getCompTypeOf(const StringId& type, void** outComps) const
{
    static int comIndices[MAX_COMPONENT_PER_ENTITY];
    uint32_t num = getCompIndexTypeOf(type, comIndices);
    for(uint32_t i=0; i<num; ++i)
    {
        outComps[i] = getComponent(comIndices[i]);
    }
    return num;
}

void EntityInstance::setTransform( const hkQsTransform& t )
{
    for (uint32_t i=0; i<m_numComps; ++i)
    {
        m_resource->getFactory(i)->transformComponent(m_comps[i], t);
    }
}

void EntityInstance::setEnabled( int index, bool bEnable )
{
    if(index < 0)
    {
        for (uint32_t i=0; i<m_numComps; ++i)
        {
            m_resource->getFactory(i)->enableComponent(m_comps[i], bEnable);
        }
    }
    else
    {
        m_resource->getFactory(index)->enableComponent(m_comps[index], bEnable);
    }
}

int EntityInstance::getFirstCompIndexTypeOf(const StringId& type) const
{
    const ComponentResource* res = m_resource->m_resources;
    for (uint32_t i = 0; i < m_numComps; ++i)
    {
        if(res[i].m_type == type)
            return i;
    }
    return -1;
}

uint32_t EntityInstance::getCompIndexTypeOf(const StringId& type, int* outIndices) const
{
    uint32_t ret = 0;
    const ComponentResource* res = m_resource->m_resources;
    for (uint32_t i = 0; i < m_numComps; ++i)
    {
        if(res[i].m_type == type)
            outIndices[ret++] = i;
    }
    return ret;
}

void* EntityInstance::getComponent(int index) const
{
    if(index < 0) return 0;
    const ComponentResource* res = m_resource->m_resources;
    ComponentFactory* fac = (ComponentFactory*)res[index].m_factory;
    if(!fac) return 0;
    return fac->lookupComponent(m_comps[index]);
}