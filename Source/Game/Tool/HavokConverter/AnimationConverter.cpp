#include "AnimationConverter.h"
#include "Animation.h"
#include "HC_Config.h"

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
#ifndef HKX_BINARY_TO_TEXT
    m_animationFile = HKX_TMP;
#else
    m_animationFile = m_config->m_exportFolder + m_name + ".havok";
#endif
}

void AnimationConverter::postProcess()
{
    HC_PROFILE(animation_post_process);

#ifdef HAVOK_COMPILE
    hkaAnimationContainer* ac = m_ac;
    ac->m_animations[0]->m_annotationTracks.clear();
    ac->m_skeletons.clear();
    ac->m_skins.clear();
    ac->m_attachments.clear();
    {
        hkPackfileWriter::Options options;
        hkOstream ostream(m_animationFile.c_str());
        hkBinaryPackfileWriter writer;
        writer.setContents(ac, hkaAnimationContainerClass);
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
    hkxNode* triggers_node = scene->findNodeByName("animation_triggers");
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
            int frame = (int)(data.m_time * ANIMATION_FRAME_FPS);
            obj << "frame" << frame;
            std::string name(longName.c_str() + trigger_prefix.length(), longName.length() - trigger_prefix.length());
            obj << "name" << name;
            triggers << obj;
            LOGI("animation trigger time = %f, frame = %d, name = %s", data.m_time, frame, name.c_str());
        }
    }

    object << "frames" << m_ac->m_animations[0]->getNumOriginalFrames();
#endif

    object << "triggers" << triggers;

#ifndef HKX_BINARY_TO_TEXT
    object << "havok_file" << m_animationFile;
#else
    std::string convert_string;
    uint32_t havok_size = 0;
    {
        FileReader reader(m_animationFile);
        binary_to_string((const unsigned char*)reader.m_buf, reader.m_size, convert_string);
        havok_size = reader.m_size;
    }
    delete_file(m_animationFile);
    object << "havok_data" << convert_string;
    object << "havok_size" << havok_size;
#endif
    return object;
}

