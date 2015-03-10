#include "AnimationConverter.h"
#include "Animation.h"

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
    HC_PROFILE(animation_post_process);

#ifdef HAVOK_COMPILE
    m_ac->m_animations[0]->m_annotationTracks.clear();
    {
        hkPackfileWriter::Options options;
        hkOstream ostream(m_animationFile.c_str());
        hkBinaryPackfileWriter writer;
        writer.setContents(m_ac, hkaAnimationContainerClass);
        if(writer.save(ostream.getStreamWriter(), options) != HK_SUCCESS)
            g_hc_config->m_error.add_error("%s write error.", BX_FUNCTION);
        LOGI("save havok animation %s", m_animationFile.c_str());
    }
#endif
}

jsonxx::Object AnimationConverter::serializeToJson() const
{
    HC_PROFILE(animation_serialize_to_json);

    jsonxx::Object object;
    jsonxx::Array triggers;

#ifdef HAVOK_COMPILE
    static const std::string trigger_prefix = "hk_trigger_";
    hkxScene* scene = m_config->m_scene;
    hkxNode* triggers_node = scene->findNodeByName("triggers");
    if(triggers_node)
    {
        dumpNodeRec(triggers_node);
        int keySize = triggers_node->m_keyFrames.getSize();
        int start = keySize < triggers_node->m_annotations.getSize() ? 1 : 0;
        for (int i=start; i<triggers_node->m_annotations.getSize(); ++i)
        {
            const hkxNode::AnnotationData& data = triggers_node->m_annotations[i];
            const hkStringPtr& text = data.m_description;
            if(!text.startsWith(trigger_prefix.c_str()))
                continue;
            std::string longName(text.cString());
            jsonxx::Object obj;
            obj << "frame" << (int)(data.m_time * ANIMATION_TIME_PERFRAME);
            std::string name(longName.c_str() + trigger_prefix.length(), longName.length() - trigger_prefix.length());
            obj << "name" << name;
            triggers << obj;
        }
    }

    object << "frames" << m_ac->m_animations[0]->getNumOriginalFrames();
#endif

    object << "triggers" << triggers;
    object << "havok_file" << m_animationFile;

    return object;
}

