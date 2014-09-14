#pragma once
#include "Prerequisites.h"
#include "StringId.h"

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

    const char*         getName() const { return m_name; };

    virtual void        init() {};
    virtual void        destroy() {};

    virtual ID          addComponent(const void* resource) = 0;
    virtual void        removeComponent(ID id) = 0;
    virtual void*       lookupComponent(ID id) = 0;
    virtual void        transformComponent(ID id, const hkQsTransform& t) {};
    virtual void        enableComponent(ID id, bool bEnable) {};
    virtual void*       listComponents() = 0; 
    virtual uint32_t    numComponents() const = 0;
    
};


