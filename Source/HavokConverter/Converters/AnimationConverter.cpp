#include "AnimationConverter.h"
#include "Utils.h"
#include "HC_Utils.h"
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>

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
    for (int i=0; i<m_ac->m_animations.getSize(); ++i)
    {
        hkaAnimation* anim = m_ac->m_animations[i];
        anim->m_annotationTracks.clear();
    }
    hkPackfileWriter::Options options;
    options.m_writeMetaInfo = false;
    hkOstream ostream(m_animationFile.c_str());
    hkBinaryPackfileWriter writer;
    writer.setContents(m_ac, hkaAnimationContainer::staticClass());
    if(writer.save(ostream.getStreamWriter(), options) != HK_SUCCESS) 
        addError(__FUNCTION__" write error.");
    LOGI("save havok animation %s", m_animationFile.c_str());
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

