#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "id_array.h"

#define MAX_COMPONENT_TYPES (64)

/*================================================

 FUNCTIONS COMPONENT MUST HAS

    void init(const void* resource);
    void setTransform(const hkQsTransform& t);
    void setEnabled(bool bEnable);
    void destroy();

================================================*/



class ComponentFactory
{
    const char*         m_name;
public:
    ComponentFactory(const char* name)
        :m_name(name)
    {

    }

    const char*                 getName() const { return m_name; };
    virtual void                init() {};
    virtual void                destroy() {};

    virtual ID                  addComponent(const void* resource) = 0;
    virtual void                removeComponent(ID id) = 0;
    virtual void*               lookupComponent(ID id) = 0;
    virtual void                transformComponent(ID id, const hkQsTransform& t) {};
    virtual void                enableComponent(ID id, bool bEnable) {};
    virtual void*               listComponents() = 0; 
    virtual uint32_t            numComponents() const = 0;
};

typedef Id ComponentId;
struct ComponentSystem
{
    virtual ~ComponentSystem() {};
    virtual const char*         getName() const = 0;
    virtual void                init() {};
    virtual void                destroy() {};
    virtual void                update(float dt) {};

    virtual ComponentId         addComponent(const void* resource) = 0;
    virtual void                removeComponent(ComponentId id) = 0;
    virtual void*               lookupComponent(ComponentId id) = 0;
    virtual void                transformComponent(ComponentId id, const hkQsTransform& t) {};
    virtual void                enableComponent(ComponentId id, bool bEnable) {};
    virtual void*               listComponents() const = 0; 
    virtual uint32_t            numComponents() const = 0;
};

template <uint32_t MAX, typename T>
struct IdComponentSystem : public ComponentSystem
{
    IdArray<MAX,T>              m_components;

    virtual ComponentId         addComponent(const void* resource) 
    {
        T inst;
        initComponent(&inst, resource);
        return id_array::create(m_components, inst);
    }

    virtual void                removeComponent(ComponentId id) 
    {
        if(!id_array::has(m_components, id)) return;
        destroyComponent(&id_array::get(m_components, id));
    }

    virtual void*               lookupComponent(ComponentId id)
    {
        if(!id_array::has(m_components, id)) return 0;
        return &id_array::get(m_components, id);
    }

    virtual void                transformComponent(ComponentId id, const hkQsTransform& t) {};
    virtual void                enableComponent(ComponentId id, bool bEnable) {};
    virtual void*               listComponents() const { return (void*)id_array::begin(m_components); };
    virtual uint32_t            numComponents() const { return id_array::size(m_components); };

protected:
    virtual void initComponent(T* inst, const void* resource) {};
    virtual void destroyComponent(T* inst) {};
};