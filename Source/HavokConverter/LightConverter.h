#pragma once
#include "stdafx.h"
#include "ComponentConverter.h"

class LightConverter   : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    LightConverter(ActorConverter* ownner);
    ~LightConverter();

    virtual std::string getTypeName() const { return LightResource::getName(); };
    virtual std::string getFormatExt() const { return LightResource::getName(); };

    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;

private:
    void process(hkxLight* light);
    
private:
    std::string                 m_name;
    hkxLight*                   m_light;
    LightResource               m_resource;
};