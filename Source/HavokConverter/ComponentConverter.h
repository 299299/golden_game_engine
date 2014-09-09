#pragma once
#include "stdafx.h"
#include "CommonUtils.h"

class EntityConverter;
class ComponentConverter : public hkReferencedObject
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    ComponentConverter(EntityConverter* ownner);
    ~ComponentConverter() =0 {};

    virtual std::string getTypeName() const = 0;
    virtual std::string getFormatExt() const = 0;
    virtual std::string combieFileName() const {
        return m_name + "." + getFormatExt();
    }
    virtual std::string getOutputFileName() const;
    virtual std::string getResourceName() const;

    virtual void process(void* pData, int hint = 0) = 0;
    virtual void postProcess() { };
    virtual jsonxx::Object serializeToJson() const = 0;
    virtual void serializeToFile(const char* fileName);
    virtual void setName(const std::string& name) { m_name = name; };
    const std::string& getName() const { return m_name; };

    virtual void writeOutput();
    virtual bool isExistInCommonPackage() const;

    std::string             m_name;
    EntityConverter*        m_ownner;
};