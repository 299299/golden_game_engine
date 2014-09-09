#pragma once
#include "stdafx.h"
#include "CommonUtils.h"

class ComponentConverter;
class EntityConverter : public hkReferencedObject
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    EntityConverter();
    virtual ~EntityConverter();

    virtual std::string getTypeName() const { return EntityResource::getName(); };
    virtual std::string getFormatExt() const { return EntityResource::getName(); };
    virtual std::string combieFileName() const {
        return m_name + "." + getFormatExt();
    }

    virtual void process(void* pData) = 0;
    virtual void postProcess();
    virtual jsonxx::Object serializeToJson() const;
    virtual jsonxx::Object serializeToJsonSplit() const;
    virtual void serializeToFile(const char* fileName);
    virtual void serializeToFileSplit(const char* fileName);

    void setName(const std::string& name) { m_name = name; };
    void setClass(const std::string& cls) { m_class = cls; };

    Entity_Config*                          m_config;
    std::vector<ComponentConverter*>        m_components;
    std::string                             m_name;
    std::string                             m_class;
};