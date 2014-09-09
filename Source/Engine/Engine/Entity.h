#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "Variant.h"

#define MAX_COMPONENT_PER_ENTITY    (16)
#define INVLIAD_ENTITY_ID   INVALID_U32
class ComponentFactory;

struct EntityID
{
    ID              m_instId : 28;
    uint32_t        m_class : 4; //max 16 entity type.

    uint32_t encode() const
    {
        return (m_class << 28 | m_instId);
    }

    void decode(uint32_t key)
    {
        m_class = key >> 28;
        m_instId = key & 0x0FFFFFFF;
    }
};


struct ComponentResource
{
    StringId                m_type;
    ComponentFactory*       m_factory;
    void*                   m_resource;
    StringId                m_resourceName;
};

ENGINE_NATIVE_ALIGN struct EntityResource
{
    DECLARE_RESOURCE(entity);

    ComponentResource*      m_resources;
    NamedVariant*           m_variants;

    uint8_t                 m_numComps;
    uint8_t                 m_class;
    uint8_t                 m_numVariants;
    char                    m_padding[1];

    uint32_t                m_resourceOffset;
    uint32_t                m_varentOffset;

    void        lookup();
    Variant*    findVariant(const StringId& name) const;
    inline ComponentFactory* getFactory(int index) const { return m_resources[index].m_factory; };
    
    void        dump();
};

void* load_resource_entity(const char* data, uint32_t size);
void  lookup_resource_entity(void * resource);


ENGINE_NATIVE_ALIGN struct EntityInstance
{
    hkQsTransform           m_transform;
    ID                      m_comps[MAX_COMPONENT_PER_ENTITY];
    const EntityResource*   m_resource;
    ID                      m_id;
    uint32_t                m_numComps;

    void         init(const void* resource);
    void         destroy();
    ID           getFirstCompIdTypeOf(const StringId& type) const;
    uint32_t     getCompIdTypeOf(const StringId& type, ID* outIDs) const;
    void*        getFirstCompTypeOf(const StringId& type) const;
    uint32_t     getCompTypeOf(const StringId& type, void** outComps) const;

    void         setTransform(const hkQsTransform& t);
    void         setEnabled(int index, bool bEnable);

    int          getFirstCompIndexTypeOf(const StringId& type) const;
    uint32_t     getCompIndexTypeOf(const StringId& type, int* outIndices) const;
    void*        getComponent(int index) const;
};
