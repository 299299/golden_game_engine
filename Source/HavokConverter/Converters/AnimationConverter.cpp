#include "AnimationConverter.h"
#include "Utils.h"
#include "HC_Utils.h"
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Serialize/Util/hkNativePackfileUtils.h>

AnimationConverter::AnimationConverter()
:m_ac(0)
{

}

AnimationConverter::~AnimationConverter()
{

}

void AnimationConverter::process( void* pData )
{
    m_ac = (hkaAnimationContainer*)pData;
    m_animationFile = m_config->m_exportFolder + m_name + ".havok";
}

void AnimationConverter::postProcess()
{
    {
        hkPackfileWriter::Options options;
        hkOstream ostream(m_animationFile.c_str());
        hkBinaryPackfileWriter writer;
        writer.setContents(m_ac, hkaAnimationContainerClass);
        if(writer.save(ostream.getStreamWriter(), options) != HK_SUCCESS) 
            addError(__FUNCTION__" write error.");
        LOGI("save havok animation %s", m_animationFile.c_str());
    }
}

jsonxx::Object AnimationConverter::serializeToJson() const
{
    jsonxx::Object object;

    jsonxx::Array triggers;
    jsonxx::Array beats;


    object << "triggers" << triggers;
    object << "beats" << beats;
    object << "havok_file" << m_animationFile;
    
    return object;
}

