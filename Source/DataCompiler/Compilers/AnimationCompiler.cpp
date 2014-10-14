#include "AnimationCompiler.h"
#include "DC_Utils.h"
#include "AnimRig.h"
#include "Utils.h"
#include <Common/Base/Algorithm/Sort/hkSort.h>

struct AnimTriggerData
{
    std::string             m_name;
    float                   m_time;
    AnimTriggerData()
    :m_time(0)
    {
    }
};

static bool compare_anim_trigger_less(const AnimTriggerData& data1, const AnimTriggerData& data2)
{
    return data1.m_time < data2.m_time;
}

AnimationCompiler::AnimationCompiler()
{

}

AnimationCompiler::~AnimationCompiler()
{
    
}

bool AnimationCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);

    std::vector<AnimTriggerData>  trigger_data;
    uint32_t triggerNum = 0;
    JsonValue triggersValue = root.GetValue("triggers");
    if(triggersValue.IsValid())
    {
        triggerNum = triggersValue.GetElementsCount();
        trigger_data.reverse(triggerNum);
        for (uint32_t i = 0; i < triggerNum; ++i)
        {
            AnimTriggerData data;
            data.m_name = JSON_GetString(triggersValue[i].GetValue("name"));
            data.m_time = JSON_GetFloat(triggersValue[i].GetValue("time"));
            trigger_data.push_back(data);
        }

        hkSort(&trigger_data[0], trigger_data.size(), compare_anim_trigger_less);
    }
    
    std::vector<AnimTriggerData> beat_data;
    uint32_t beatNum = 0;
    JsonValue beatsValue = root.GetValue("beats");
    if(beatsValue.IsValid())
    {
        beatNum = beatsValue.GetElementsCount();
        beat_data.reverse(beatNum);
        for (uint32_t i = 0; i < triggerNum; ++i)
        {
            AnimTriggerData data;
            data.m_name = JSON_GetString(beatsValue[i].GetValue("name"));
            data.m_time = JSON_GetFloat(beatsValue[i].GetValue("time"));
            beat_data.push_back(data);
        }

        hkSort(&beat_data[0], beat_data.size(), compare_anim_trigger_less);
    }

    std::string havokFile = JSON_GetString(root.GetValue("havok_file"));
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        addError(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
        return false;
    }
    
    uint32_t havokOffset = sizeof(Animation) + beatNum * sizeof(AnimationBeat) + triggerNum * sizeof(triggerNum);
    havokOffset = HK_NEXT_MULTIPLE_OF(16, havokOffset);
    uint32_t memSize = havokOffset + havokReader.m_size;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);
    
    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;
    memcpy(offset + havokOffset, havokReader.m_buf, havokReader.m_size);

    Animation* anim = (Animation*)mem.m_buf;
    JsonValue mirrorValue = root.GetValue("mirrored_from");
    if(mirrorValue.IsValid())
    {
        std::string mirrorFile = JSON_GetString(root.GetValue("mirrored_from"));
        anim->m_mirroredFrom = StringId(mirrorFile.c_str());
        addDependency("mirror animation", name_to_file_path(mirrorFile, Animation::get_name()));

        std::string rigFile = JSON_GetString(root.GetValue("rig"));
        anim->m_rigName = StringId(rigFile.c_str());
        addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));
    }

    anim->m_numBeats = beatNum;
    anim->m_numTriggers = triggerNum;
    offset += sizeof(Animation);
    anim->m_triggers = (AnimationTrigger*)offset;
    offset += (triggerNum * sizeof(triggerNum));
    anim->m_beats = (AnimationBeat*)offset;
    anim->m_havokDataOffset = havokOffset;
    anim->m_havokDataSize = havokReader.m_size;
    
    for (uint32_t i=0; i<anim->m_numTriggers; ++i)
    {
        anim->m_triggers[i].m_name = StringId(trigger_data[i].m_name.c_str());
        anim->m_triggers[i].m_time = trigger_data[i].m_time;
    }
    
    extern const char* g_beatTypeNames[];
    for(uint32_t i=0; i<anim->m_numBeats; ++i)
    {
        anim->m_beats[i].m_type = find_enum_index(beat_data[i].m_name.c_str(), g_beatTypeNames);
        anim->m_beats[i].m_time = beat_data[i].m_time;
    }
    
    return write_file(m_output, mem.m_buf, memSize);
}