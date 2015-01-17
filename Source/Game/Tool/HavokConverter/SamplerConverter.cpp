#include "SamplerConverter.h"
#include "ActorConverter.h"
#include "ToolUtils.h"
#include "Texture.h"

SamplerConverter::SamplerConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
,m_type(0)
,m_textureFormat(DDS_FORMAT)
{

}

SamplerConverter::~SamplerConverter()
{

}

void SamplerConverter::process( void* pData, int hint /*= 0*/ )
{

}

jsonxx::Object SamplerConverter::serializeToJson() const
{
    jsonxx::Object object;
    object << "name" << m_textureSlotName;
    jsonxx::Array flags;
    for (uint32_t i=0; i<m_flags.size();++i)
    {
        flags << m_flags[i];
    }
    object << "flags" << flags;

    jsonxx::Object textureObject;
    textureObject << "name" << m_ownner->m_config->m_rootPath + m_name;
    textureObject << "input" << m_textureFileName;
    textureObject << "format" << std::string(m_textureFormat);

    object << "texture" << textureObject;

    return object;
}
