#include "AnimationCompiler.h"
#include "DC_Utils.h"
#include "AnimRig.h"

AnimationCompiler::AnimationCompiler()
{

}

AnimationCompiler::~AnimationCompiler()
{
    
}

bool AnimationCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    uint32_t triggerNum = 0;
    JsonValue triggersValue = root.GetValue("triggers");
    if(triggersValue.IsValid())
    {
        triggerNum = triggersValue.GetElementsCount();
    }
    
    uint32_t beatNum = 0;
    JsonValue beatsValue = root.GetValue("beats");
    if(beatsValue.IsValid())
    {
        beatNum = beatsValue.GetElementsCount();
    }

    
    std::string havokFile = JSON_GetString(root.GetValue("havok_file"));
    char* havokData = 0;
    uint32_t havokFileSize = read_file(havokFile.c_str(), &havokData);
    if(havokFileSize < 16)
    {
        addError(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
        return false;
    }
    
    uint32_t havokOffset = sizeof(Animation) + beatNum * sizeof(AnimationBeat) + triggerNum * sizeof(triggerNum);
    havokOffset = HK_NEXT_MULTIPLE_OF(16, havokOffset);
    uint32_t memSize = havokOffset + havokFileSize;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);
    
    char* p = (char*)malloc(memSize);
    char* offset = p;
    memset(p, 0x00, memSize);
    memcpy(p + havokOffset, havokData, havokFileSize);
    free(havokData);

    Animation* anim = (Animation*)p;
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
    anim->m_havokDataSize = havokFileSize;
    
    for (uint32_t i=0; i<anim->m_numTriggers; ++i)
    {
        AnimationTrigger& trigger = anim->m_triggers[i];
        const JsonValue& triggerValue = triggersValue[i];
        trigger.m_name = JSON_GetStringId(triggerValue.GetValue("name"));
        trigger.m_time = JSON_GetFloat(triggerValue.GetValue("time"));
    }
    
    extern const char* g_beatTypeNames[];
    for(uint32_t i=0; i<anim->m_numBeats; ++i)
    {
        AnimationBeat& beat = anim->m_beats[i];
        const JsonValue& beatValue = beatsValue[i];
        beat.m_type = JSON_GetEnum(beatValue.GetValue("name"), g_beatTypeNames);
        beat.m_time = JSON_GetFloat(beatValue.GetValue("time"));
    }
    
    bool bRet = write_file(m_output, p, memSize);
    free(p);
    return bRet;
}