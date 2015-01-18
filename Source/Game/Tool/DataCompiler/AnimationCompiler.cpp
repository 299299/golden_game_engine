#include "AnimationCompiler.h"
#include "AnimRig.h"

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

bool AnimationCompiler::readJSON(const jsonxx::Object& root)
{
    __super::readJSON(root);

    std::vector<AnimTriggerData>  trigger_data;
    uint32_t triggerNum = 0;

    if(root.has<jsonxx::Array>("triggers"))
    {
        jsonxx::Array triggersValue = root.get<jsonxx::Array>("triggers");
        triggerNum = triggersValue.size();
        trigger_data.reserve(triggerNum);
        for (uint32_t i = 0; i < triggerNum; ++i)
        {
            AnimTriggerData data;
            const jsonxx::Object& triggerValue = triggersValue.get<jsonxx::Object>(i);
            data.m_name = triggerValue.get<std::string>("name");
            data.m_time = triggerValue.get<float>("time");
            trigger_data.push_back(data);
        }

        if(!trigger_data.empty()) 
            std::sort(trigger_data.begin(), trigger_data.end(), compare_anim_trigger_less);
    }
     
    std::vector<AnimTriggerData> beat_data;
    uint32_t beatNum = 0;
    if(root.has<jsonxx::Array>("beats"))
    {
        jsonxx::Array beatsValue = root.get<jsonxx::Array>("beats");
        beatNum = beatsValue.size();
        beat_data.reserve(beatNum);
        for (uint32_t i = 0; i < beatNum; ++i)
        {
            AnimTriggerData data;
            const jsonxx::Object& beatValue = beatsValue.get<jsonxx::Object>(i);
            data.m_name = beatValue.get<std::string>("name");
            data.m_time = beatValue.get<float>("time");
            beat_data.push_back(data);
        }

        if(!beat_data.empty()) 
            std::sort(beat_data.begin(), beat_data.end(), compare_anim_trigger_less);
    }

    std::string havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        g_config->m_error.add_error(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
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
    if(root.has<jsonxx::Object>("mirrored"))
    {
        const jsonxx::Object& mirrorObject = root.get<jsonxx::Object>("mirrored");
        const std::string& mirrorFile = mirrorObject.get<std::string>("animation");
        const std::string& rigFile = mirrorObject.get<std::string>("rig");
        anim->m_mirroredFrom = StringId(mirrorFile.c_str());
        anim->m_rigName = StringId(rigFile.c_str());
        addDependency("mirror animation", name_to_file_path(mirrorFile, Animation::get_name()));
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