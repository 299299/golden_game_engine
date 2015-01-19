#include "AnimRigCompiler.h"
#include "Animation.h"

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

bool AnimRigCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    jsonxx::Array jointsValue = root.get<jsonxx::Array>("joints");
    uint32_t jointNum = jointsValue.size();
    uint32_t attachmentNum = 0;
    if(root.has<jsonxx::Array>("attachments"))
    {
        attachmentNum = root.get<jsonxx::Array>("attachments").size();
    }

#if 0
	JsonValue animationsValue = root.GetValue("animation-set");
	uint32_t animationsNum = 0;
	if(animationsValue.IsValid()) animationsNum = animationsValue.GetElementsCount();
#endif

    uint32_t memSize = sizeof(AnimRig) + jointNum*sizeof(StringId) + attachmentNum*sizeof(BoneAttachment);
	uint32_t headerSize = memSize;
    memSize = NEXT_MULTIPLE_OF(16, memSize);
    uint32_t havokOffset = memSize;

    const std::string& havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    uint32_t havokFileSize = havokReader.m_size;
    if(havokFileSize < 16)
    {
        g_config->m_error.add_error(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
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
    rig->m_jointNum = root.get<int>("joint_num");
    rig->m_mirrored = root.get<bool>("mirrored");

    offset += sizeof(AnimRig);
	//-----------------------------------------------
	//					joint names
	//-----------------------------------------------
    rig->m_jointNames = (StringId*)(offset);
    for(uint32_t i=0; i<jointNum; ++i)
    {
        rig->m_jointNames[i] = StringId(jointsValue.get<std::string>(i).c_str());
    }

    if(root.has<jsonxx::Object>("human_body"))
    {
        extern const char*  g_humanBodyNames[];
        jsonxx::Object humanPartValue = root.get<jsonxx::Object>("human_body");
        for(int i=0; i<kBodyPartMax; ++i)
        {
            StringId name = StringId(humanPartValue.get<std::string>(g_humanBodyNames[i]).c_str());
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
#if 0
	for (uint32_t i=0; i<animationsNum; ++i)
	{
		std::string animName = JSON_GetString(animationsValue[i]);
		addDependency("animation-set-anim", name_to_file_path(animName, Animation::get_name()));
		rig->m_animNames[i] = StringId(animName.c_str());
	}
	offset += animationsNum * (sizeof(StringId)+sizeof(void*));
#endif
	//-----------------------------------------------
	//					bone attachments
	//-----------------------------------------------
    rig->m_attachments = (BoneAttachment*)offset;
    rig->m_attachNum = attachmentNum;
    if(attachmentNum)
    {
        const jsonxx::Array& attachmentsValue = root.get<jsonxx::Array>("attachments");
        for (uint32_t i = 0; i < attachmentNum; ++i)
        {
            const jsonxx::Object& attachmentValue = attachmentsValue.get<jsonxx::Object>(i);
            BoneAttachment& ba = rig->m_attachments[i];
            ba.m_name = StringId(attachmentValue.get<std::string>("name").c_str());
            ba.m_boneIndex = attachmentValue.get<int>("bone");
            json_to_floats(attachmentValue.get<jsonxx::Array>("transform"), ba.m_boneFromAttachment, 16);
        }
    }

	offset += attachmentNum * sizeof(BoneAttachment);
	ENGINE_ASSERT((offset-mem.m_buf == headerSize), "anim-rig mem offset error.");
    return write_file(m_output, mem.m_buf, memSize);
}