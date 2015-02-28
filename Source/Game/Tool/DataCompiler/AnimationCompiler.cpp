#include "AnimationCompiler.h"
#include "AnimRig.h"
#include "Animation.h"

struct AnimTriggerData
{
    std::string             m_name;
    float                   m_time;
    AnimTriggerData()
    :m_time(0)
    {
    }
};

INTERNAL bool compare_anim_trigger_less(const AnimTriggerData& data1, const AnimTriggerData& data2)
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
    BaseCompiler::readJSON(root);

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
            const jsonxx::Object& o = triggersValue.get<jsonxx::Object>(i);
            data.m_name = o.get<std::string>("name");
            data.m_time = json_to_float(o, "time");
            trigger_data.push_back(data);
        }

        if(!trigger_data.empty())
            std::sort(trigger_data.begin(), trigger_data.end(), compare_anim_trigger_less);
    }

    std::string havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        g_config->m_error.add_error("%s can not find havok file [%s]", BX_FUNCTION, havokFile.c_str());
        return false;
    }

    uint32_t havokOffset = sizeof(Animation) + triggerNum * sizeof(triggerNum);
    havokOffset = NATIVE_ALGIN_SIZE(havokOffset);
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
        anim->m_mirrored_from = stringid_caculate(mirrorFile.c_str());
        anim->m_rig_name = stringid_caculate(rigFile.c_str());
        addDependency("mirror animation", name_to_file_path(mirrorFile, EngineNames::ANIMATION));
        addDependency("rig", name_to_file_path(rigFile, EngineNames::ANIMATION));
    }

    anim->m_num_triggers = triggerNum;
    offset += sizeof(Animation);
    anim->m_trigger_offset = sizeof(Animation);
    AnimationTrigger* triggers = (AnimationTrigger*)offset;
    offset += (triggerNum * sizeof(triggerNum));
    anim->m_havok_data_offset = havokOffset;
    anim->m_havok_data_size = havokReader.m_size;

    for (uint32_t i=0; i<triggerNum; ++i)
    {
        triggers[i].m_name = stringid_caculate(trigger_data[i].m_name.c_str());
        triggers[i].m_time = trigger_data[i].m_time;
    }

    return write_file(m_output, mem.m_buf, memSize);
}