#pragma once
#include "ComponentConverter.h"

class SamplerConverter  : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    SamplerConverter(ActorConverter* ownner);
    ~SamplerConverter();

    virtual std::string getTypeName() const { return EngineNames::TEXTURE; };
    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;

    std::vector<std::string>        m_flags;
    std::string                     m_textureFileName;
    std::string                     m_textureSlotName;
    std::string                     m_textureFormat;
    int                             m_type;
};