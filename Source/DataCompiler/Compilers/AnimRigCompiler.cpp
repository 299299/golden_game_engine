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
	JsonValue animationsValue = root.GetValue("animation-set");
	uint32_t animationsNum = 0;
	if(animationsValue.IsValid()) animationsNum = animationsValue.GetElementsCount();

    uint32_t memSize = sizeof(AnimRig) + jointNum*sizeof(StringId) + attachmentNum*sizeof(BoneAttachment) + 
		animationsNum*sizeof(StringId) + animationsNum*sizeof(void*);
	uint32_t headerSize = memSize;
    memSize = HK_NEXT_MULTIPLE_OF(16, memSize);
    uint32_t havokOffset = memSize;

    std::string havokFile = JSON_GetString(root.GetValue("havok_file"));
    FileReader havokReader(havokFile);
    uint32_t havokFileSize = havokReader.m_size;
    if(havokFileSize < 16)
    {
        addError(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
        return false;
    }

    memSize += havokFileSize;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);

    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;

    char* havokP = offset + havokOffset;
    memcpy(havokP, havokReader.m_buf, havokFileSize);

    AnimRig* rig = (AnimRig*)offset;
    rig->m_havokDataOffset = havokOffset;
    rig->m_havokDataSize = havokFileSize;
    rig->m_jointNum = JSON_GetInt(root.GetValue("joint_num"));
    rig->m_mirrored = JSON_GetBool(root.GetValue("mirrored"));
	rig->m_numAnimations = animationsNum;

    offset += sizeof(AnimRig);
	//-----------------------------------------------
	//					joint names
	//-----------------------------------------------
    rig->m_jointNames = (StringId*)(offset);
    for(uint32_t i=0; i<jointNum; ++i)
    {
        rig->m_jointNames[i] = JSON_GetStringId(jointsValue[i]);
    }
    JsonValue humanPartValue = root.GetValue("human_body");
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
	
	//-----------------------------------------------
	//					animation-set names
	//-----------------------------------------------
	rig->m_animNames=(StringId*)offset;
	for (uint32_t i=0; i<animationsNum; ++i)
	{
		std::string animName = JSON_GetString(animationsValue[i]);
		addDependency("animation-set-anim", name_to_file_path(animName, Animation::get_name()));
		rig->m_animNames[i] = StringId(animName.c_str());
	}
	offset += animationsNum * (sizeof(StringId)+sizeof(void*));

	//-----------------------------------------------
	//					bone attachments
	//-----------------------------------------------
    rig->m_attachments = (BoneAttachment*)offset;
    rig->m_attachNum = attachmentNum;
    for (uint32_t i = 0; i < attachmentNum; ++i)
    {
        JsonValue attachmentValue = attachmentsValue[i];
        BoneAttachment& ba = rig->m_attachments[i];
        ba.m_name = JSON_GetStringId(attachmentValue.GetValue("name"));
        ba.m_boneIndex = JSON_GetInt(attachmentValue.GetValue("bone"));
        JSON_GetFloats(attachmentValue.GetValue("transform"), ba.m_boneFromAttachment, 16);
    }
	offset += attachmentNum * sizeof(BoneAttachment);
	ENGINE_ASSERT((offset-mem.m_buf == headerSize), "anim-rig mem offset error.");
    
    return write_file(m_output, mem.m_buf, memSize);
}