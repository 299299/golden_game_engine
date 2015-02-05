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
    memSize = NEXT_MULTIPLE_OF(16, memSize);
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
    rig->m_havokDataOffset = havokOffset;
    rig->m_havokDataSize = havokFileSize;
    rig->m_jointNum = json_to_int(root, "joint_num");
    rig->m_mirrored = root.get<bool>("mirrored", false);

    offset += sizeof(AnimRig);
    //-----------------------------------------------
    //                  joint names
    //-----------------------------------------------
    rig->m_jointNames = (StringId*)(offset);
    for(uint32_t i=0; i<jointNum; ++i)
    {
        rig->m_jointNames[i] = stringid_caculate(jointsValue.get<std::string>(i).c_str());
    }

    if(root.has<jsonxx::Object>("human_body"))
    {
        extern const char*  g_humanBodyNames[];
        jsonxx::Object humanPartValue = root.get<jsonxx::Object>("human_body");
        for(int i=0; i<kBodyPartMax; ++i)
        {
            StringId name = json_to_stringid(humanPartValue, g_humanBodyNames[i]);
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
    //                  bone attachments
    //-----------------------------------------------
    rig->m_attachments = (BoneAttachment*)offset;
    rig->m_attachNum = attachmentNum;
    if(attachmentNum)
    {
        const jsonxx::Array& attachmentsValue = root.get<jsonxx::Array>("attachments");
        for (uint32_t i = 0; i < attachmentNum; ++i)
        {
            const jsonxx::Object& o = attachmentsValue.get<jsonxx::Object>(i);
            BoneAttachment& ba = rig->m_attachments[i];
            ba.m_name = json_to_stringid(o, "name");
            ba.m_boneIndex = json_to_int(o, "bone");
            json_to_floats(o, "transform", ba.m_boneFromAttachment, 16);
        }
    }

    offset += attachmentNum * sizeof(BoneAttachment);
    ENGINE_ASSERT((offset-mem.m_buf == (int)headerSize), "anim-rig mem offset error.");
    return write_file(m_output, mem.m_buf, memSize);
}