#pragma once
#include "HC_Config.h"

class ComponentConverter;
class ActorConverter : public hkReferencedObject
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    ActorConverter();
    virtual ~ActorConverter();

    virtual std::string getTypeName() const { return EngineNames::ACTOR; };
    virtual std::string getResourceName() const;

    virtual void process(void* pData) = 0;
    virtual void postProcess();
    virtual jsonxx::Object serializeToJson() const;
    virtual void serializeToFile(const std::string& fileName);

    void setName(const std::string& name) { m_name = name; };
    void setClass(const std::string& cls) { m_class = cls; };

    hkxNode* findNode(const char* name);

    Actor_Config*                           m_config;
    std::vector<ComponentConverter*>        m_components;
    std::string                             m_name;
    std::string                             m_class;
};