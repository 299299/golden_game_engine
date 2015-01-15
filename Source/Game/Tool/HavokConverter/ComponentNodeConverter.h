#pragma once
#include "ComponentConverter.h"

class ComponentNodeConverter : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    ComponentNodeConverter(ActorConverter* ownner);
    ~ComponentNodeConverter();

    virtual std::string getTypeName() const { return m_typeName; };
    virtual std::string getFormatExt() const { return m_typeName; };

    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;
    
    std::string                     m_typeName;
    hkxNode*                        m_node;
    const hkxAttributeGroup*        m_attributes;
};