#include "AnimRigCompiler.h"
#include "Animation.h"
#include "AnimRig.h"

static int find_joint_index(StringId name, StringId* names, int size)
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

    uint32_t memSize = sizeof(AnimRig) + jointNum*sizeof(StringId) + attachmentNum*sizeof(BoneAttachment);
    uint32_t headerSize = memSize;
    memSize = NATIVE_ALGIN_SIZE(memSize);
    uint32_t havokOffset = memSize;

    const std::string& havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    uint32_t havokFileSize = havokReader.m_size;
    if(havokFileSize < 16)
    {
        g_config->m_error.add_error("%s can not find havok file [%s]", BX_FUNCTION, havokFile.c_str());
        return false;
    }

    memSize += havokFileSize;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);

    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;

    char* havokP = offset + havokOffset;
    memcpy(havokP, havokReader.m_buf, havokFileSize);

    AnimRig* rig = (AnimRig*)offset;
    rig->m_havok_data_offset = havokOffset;
    rig->m_havok_data_size = havokFileSize;
    rig->m_joint_num = json_to_int(root, "joint_num");
    rig->m_mirrored = root.get<bool>("mirrored", false);
    rig->m_joint_name_offset = sizeof(AnimRig);

    offset += sizeof(AnimRig);
    //-----------------------------------------------
    //                  joint names
    //-----------------------------------------------
    StringId* names = (StringId*)(offset);
    for(uint32_t i=0; i<jointNum; ++i)
    {
        names[i] = stringid_caculate(jointsValue.get<std::string>(i).c_str());
    }

    if(root.has<jsonxx::Object>("human_body"))
    {
        extern const char*  g_humanBodyNames[];
        jsonxx::Object humanPartValue = root.get<jsonxx::Object>("human_body");
        for(int i=0; i<kBodyPartMax; ++i)
        {
            StringId name = json_to_stringid(humanPartValue, g_humanBodyNames[i]);
            rig->m_human_joint_indices[i] = find_joint_index(name, names, jointNum);
        }
    }
    else
    {
        for(int i=0; i<kBodyPartMax; ++i)
        {
            rig->m_human_joint_indices[i] = -1;
        }
    }
    offset += jointNum * sizeof(StringId);

    //-----------------------------------------------
    //                  bone attachments
    //-----------------------------------------------
    rig->m_attachment_offset = (uint32_t)(offset - mem.m_buf);
    rig->m_attach_num = attachmentNum;
    BoneAttachment* attachments = (BoneAttachment*)(mem.m_buf + rig->m_attachment_offset);

    if(attachmentNum)
    {
        const jsonxx::Array& attachmentsValue = root.get<jsonxx::Array>("attachments");
        for (uint32_t i = 0; i < attachmentNum; ++i)
        {
            const jsonxx::Object& o = attachmentsValue.get<jsonxx::Object>(i);
            BoneAttachment& ba = attachments[i];
            ba.m_name = json_to_stringid(o, "name");
            ba.m_bone_index = json_to_int(o, "bone");
            json_to_floats(o, "transform", ba.m_bone_from_attachment, 16);
        }
    }

    offset += attachmentNum * sizeof(BoneAttachment);
    ENGINE_ASSERT((offset-mem.m_buf == (int)headerSize), "anim-rig mem offset error.");
    return write_file(m_output, mem.m_buf, memSize);
}