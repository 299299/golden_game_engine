#pragma once
#include "Component.h"
#include "DataDef.h"
#include "MemoryPool.h"

template <typename T>
class DynamicObjectComponentFactory : public ComponentFactory
{
public:
    DynamicObjectArray<T>           m_objects;
    uint32_t                        m_capacity;

    DynamicObjectComponentFactory(const char* name, uint32_t max_num)
        :ComponentFactory(name)
        ,m_capacity(max_num)
    {

    }
    virtual void init()
    {
        INIT_STATIC_POOL(m_objects, m_capacity);
    }
    virtual void destroy()
    {
        for (uint32_t i=0; i<m_objects.getSize();++i)
        {
            m_objects[i].destroy();
        }
    }
    virtual ID      addComponent(const void* resource) 
    {
        T& inst = m_objects.addObject();
        inst.init(resource);
        return inst.m_id;
    }
    virtual void    removeComponent(ID compId) 
    {
        if(!m_objects.has(compId))
        {
            LOGE(__FUNCTION__" compId not valid %d.", compId);
            return;
        }
        m_objects.lookup(compId).destroy();
        m_objects.remove(compId);
    }
    virtual void*   lookupComponent(ID compId) 
    {
        if(!m_objects.has(compId))
        {
            LOGE(__FUNCTION__" compId not valid %d.", compId);
            return 0;
        }
        return &m_objects.lookup(compId);
    }
    virtual void    transformComponent(ID compId, const hkQsTransform& t) 
    {
        if(!m_objects.has(compId))
        {
            LOGE(__FUNCTION__" compId not valid %d.", compId);
            return;
        }
        m_objects.lookup(compId).setTransform(t);
    };
    virtual void    enableComponent(ID compId, bool bEnable) 
    {
        if(!m_objects.has(compId))
        {
            LOGE(__FUNCTION__" compId not valid %d.", compId);
            return;
        }
        m_objects.lookup(compId).setEnabled(bEnable);
    };
    virtual void*   listComponents() 
    {
        return m_objects.begin();
    }
    virtual uint32_t numComponents() const
    {
        return m_objects.getSize();
    }
    T& getComponent(uint32_t index) 
    {
        return m_objects[index];
    }
};

struct ComponentManager
{
    ComponentFactory**              m_factories;
    StringId*                       m_types;
    uint32_t                        m_numFactories;
    uint32_t                        m_maxNumFactories;

    inline ComponentFactory* findFactory(const StringId& typeName)
    {
        for(uint32_t i=0; i<m_numFactories; ++i)
        {
            if(m_types[i] == typeName)
                return m_factories[i];
        }
        return 0;
    }

    inline void registerFactory(ComponentFactory* factory)
    {
        m_types[m_numFactories] = StringId(factory->getName()); 
        m_factories[m_numFactories++] = factory;
        HK_ASSERT(0, m_numFactories < m_maxNumFactories);
    }

    inline ID addComponent(const StringId& type, const void* resource)
    {
        if(!resource) return INVALID_ID;
        ComponentFactory* fac  = findFactory(type);
        if(!fac) return INVALID_ID;
        return fac->addComponent(resource);
    }

    inline void removeComponent(const StringId& type, ID compId)
    {
        ComponentFactory* fac  = findFactory(type);
        if(!fac) return;
        fac->removeComponent(compId);
    }

    inline void* lookupComponent(const StringId& type, ID compId)
    {
        ComponentFactory* fac  = findFactory(type);
        if(!fac) return 0;
        return fac->lookupComponent(compId);
    }

    inline void setTransform(const StringId& type, const hkQsTransform& t, ID compId)
    {
        ComponentFactory* fac  = findFactory(type);
        if(!fac) return;
        fac->transformComponent(compId, t);
    }

    inline void setEnabled(const StringId& type, bool bEnabled, ID compId)
    {
        ComponentFactory* fac  = findFactory(type);
        if(!fac) return;
        return fac->enableComponent(compId, bEnabled);
    }

    inline void* listComponents(const StringId& type)
    {
        ComponentFactory* fac  = findFactory(type);
        if(!fac) return 0;
        return fac->listComponents();
    }

    inline uint32_t numComponents(const StringId& type)
    {
        ComponentFactory* fac  = findFactory(type);
        if(!fac) return 0;
        return fac->numComponents();
    }

    void init(uint32_t maxNum = MAX_COMPONENT_TYPES);
    void initFactories()
    {
        for (uint32_t i=0; i<m_numFactories; ++i)
        {
            m_factories[i]->init();
        }
    }

    void destroy()
    {
        for (uint32_t i=0; i<m_numFactories; ++i)
        {
            m_factories[i]->destroy();
        }
    }
};

extern ComponentManager g_componentMgr;