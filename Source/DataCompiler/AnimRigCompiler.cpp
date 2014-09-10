#include "AnimRigCompiler.h"
#include "DC_Utils.h"

static int find_joint_index(const StringId& name, StringId* names, int size)
{
    for(int i=0; i<size; ++i)
    {
        if(name == names[i]) return i;
    }
    return -1;
}

AnimRigCompiler::AnimRigCompiler()
{

}

AnimRigCompiler::~AnimRigCompiler()
{

}

bool AnimRigCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    JsonValue jointsValue = root.GetValue("joints");
    uint32_t jointNum = 0;
    if(jointsValue.IsValid()) jointNum = jointsValue.GetElementsCount();
    JsonValue attachmentsValue = root.GetValue("attachments");
    uint32_t attachmentNum = 0;
    if(attachmentsValue.IsValid()) attachmentNum = attachmentsValue.GetElementsCount();

    uint32_t memSize = sizeof(AnimRig) + jointNum*sizeof(StringId) + attachmentNum*sizeof(BoneAttachment);
    memSize = HK_NEXT_MULTIPLE_OF(16, memSize);
    uint32_t havokOffset = memSize;

    std::string havokFile = JSON_GetString(root.GetValue("havok-file"));
    char* havokData = 0;
    uint32_t havokFileSize = read_file(havokFile.c_str(), &havokData);
    if(havokFileSize < 16)
    {
        addError(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
        return false;
    }

    memSize += havokFileSize;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);

    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    char* offset = p;

    char* havokP = p + havokOffset;
    memcpy(havokP, havokData, havokFileSize);
    free(havokData);

    AnimRig* rig = (AnimRig*)p;
    rig->m_havokDataOffset = havokOffset;
    rig->m_havokDataSize = havokFileSize;
    rig->m_jointNum = JSON_GetInt(root.GetValue("joint-num"));
    rig->m_mirrored = JSON_GetBool(root.GetValue("mirrored"));
    offset += sizeof(AnimRig);
    rig->m_jointNames = (StringId*)(offset);
    for(uint32_t i=0; i<jointNum; ++i)
    {
        rig->m_jointNames[i] = JSON_GetStringId(jointsValue[i]);
    }
    JsonValue humanPartValue = root.GetValue("human-body");
    if(humanPartValue.IsValid())
    {
        extern const char*  g_humanBodyNames[];
        for(int i=0; i<kBodyPartMax; ++i)
        {
            StringId name = JSON_GetStringId(humanPartValue.GetValue(g_humanBodyNames[i]));
            rig->m_humanJointIndices[i] = find_joint_index(name, rig->m_jointNames, jointNum);
        }
    }
    else 
    {
        for(int i=0; i<kBodyPartMax; ++i)
        {
            rig->m_humanJointIndices[i] = -1;
        }
    }
    offset += jointNum*sizeof(StringId);
    rig->m_attachments = (BoneAttachment*)offset;
    for (uint32_t i = 0; i < attachmentNum; ++i)
    {
        JsonValue attachmentValue = attachmentsValue[i];
        BoneAttachment& ba = rig->m_attachments[i];
        ba.m_name = JSON_GetStringId(attachmentValue.GetValue("name"));
        ba.m_boneIndex = JSON_GetInt(attachmentValue.GetValue("bone"));
        JSON_GetFloats(attachmentValue.GetValue("transform"), ba.m_transform, 16);
    }
    
    bool bRet = write_file(m_output, p, memSize);
    free(p);
    return bRet;
}