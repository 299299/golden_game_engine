#pragma once
#include "HC_Config.h"

class hkxNode;
class ActorConverter;


class ComponentConverter : public hkReferencedObject
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    ComponentConverter(ActorConverter* ownner);
    virtual ~ComponentConverter() {};

    virtual std::string getTypeName() const = 0;
    virtual std::string getResourceName() const;

    virtual void process(void* pData, int hint = 0) = 0;
    virtual void postProcess() { };
    virtual jsonxx::Object serializeToJson() const { return jsonxx::Object(); };
    virtual void setName(const std::string& name) { m_name = name; };
    const std::string& getName() const { return m_name; };
    virtual void fillAttributes(jsonxx::Object& object) const;

    std::string                 m_name;
    ActorConverter*             m_ownner;
    hkxNode*                    m_node;
};