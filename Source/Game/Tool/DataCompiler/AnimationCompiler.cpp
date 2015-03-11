#include "AnimationCompiler.h"
#include "AnimRig.h"
#include "Animation.h"

struct AnimTriggerData
{
    std::string             m_name;
    int                     m_frame;
    AnimTriggerData()
    :m_frame(0)
    {
    }
};

INTERNAL bool compare_anim_trigger_less(const AnimTriggerData& data1, const AnimTriggerData& data2)
{
    return data1.m_frame < data2.m_frame;
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
    uint32_t frames = json_to_int(root, "frames");

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
            data.m_frame = json_to_int(o, "frame");
            if(data.m_frame == frames)
                data.m_frame = frames - 1;
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

    uint32_t havokOffset = sizeof(Animation)  + frames * sizeof(uint32_t) * 2 + triggerNum * sizeof(AnimationTrigger);
    havokOffset = NATIVE_ALGIN_SIZE(havokOffset);
    uint32_t memSize = havokOffset + havokReader.m_size;
    memSize = NATIVE_ALGIN_SIZE(memSize);

    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);

    MemoryBuffer mem(memSize);
    memcpy(mem.m_buf + havokOffset, havokReader.m_buf, havokReader.m_size);

    Animation* anim = (Animation*)mem.m_buf;
    anim->m_num_frames = frames;

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

    anim->m_trigger_offsets = sizeof(Animation);
    anim->m_havok_data_offset = havokOffset;
    anim->m_havok_data_size = havokReader.m_size;

    uint32_t* offsets = (uint32_t*)(mem.m_buf + anim->m_trigger_offsets);
    char* triggers = mem.m_buf + anim->m_trigger_offsets + sizeof(uint32_t)*frames;

    std::map<int, std::vector<AnimTriggerData*> > trigger_maps;
    for (uint32_t i=0; i<triggerNum; ++i)
    {
        trigger_maps[trigger_data[i].m_frame].push_back(&trigger_data[i]);
    }

    for (int i=0; i<(int)frames; ++i)
    {
        std::map<int, std::vector<AnimTriggerData*> >::iterator iter = trigger_maps.find(i);
        int num = 0;
        if (iter != trigger_maps.end())
        {
            num = iter->second.size();
        }
        offsets[i] = (int)(triggers - mem.m_buf);
        *((uint32_t*)triggers) = num;
        triggers += sizeof(uint32_t);
        AnimationTrigger* t = (AnimationTrigger*)triggers;
        for (int j=0; j<num; ++j)
        {
            AnimTriggerData* d = iter->second[j];
            t[j].m_name = stringid_caculate(d->m_name.c_str());
        }
        triggers += num*sizeof(AnimationTrigger);
    }
    
    int r = triggers - mem.m_buf;
    int t = sizeof(Animation)  + frames * sizeof(uint32_t) * 2 + triggerNum * sizeof(AnimationTrigger);

    ENGINE_ASSERT(r == t, "havok offset check");
    ENGINE_ASSERT(anim->m_havok_data_size == havokReader.m_size, "havok offset check");
    ENGINE_ASSERT(anim->m_havok_data_offset == havokOffset, "havok offset check");

    return write_file(m_output, mem.m_buf, memSize);
}