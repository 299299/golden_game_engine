#pragma once
#include "ComponentConverter.h"
#include "Light.h"

class LightConverter   : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    LightConverter(ActorConverter* ownner);
    ~LightConverter();

    virtual std::string getTypeName() const { return LightResource::get_name(); };
    virtual std::string getFormatExt() const { return LightResource::get_name(); };

    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;
    
private:
    hkxLight*                   m_light;
    LightResource               m_resource;
};