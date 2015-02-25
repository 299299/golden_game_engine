#include "AnimRigConverter.h"
#include "ModelConverter.h"
#include "ActorConverter.h"
#include "AnimRig.h"

const char* g_body_names_0[] =
{
    "head",
    "neck",
    "leftshoulder",
    "leftarm",
    "leftforearm",
    "lefthand",
    "rightshoulder",
    "rightarm",
    "rightforearm",
    "righthand",
    "hips",
    "leftupleg",
    "leftleg",
    "leftfoot",
    "rightupleg",
    "rightleg",
    "rightfoot",
};

AnimRigConverter::AnimRigConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
,m_skin(0)
{
    for (uint32_t i=0; i<kBodyPartMax; ++i)
    {
        m_bodyPart[i] = -1;
    }
}

AnimRigConverter::~AnimRigConverter()
{

}

void AnimRigConverter::process(void* pData, int hint)
{
    process((RigSkinData*)pData);
}

void AnimRigConverter::process(RigSkinData* skin)
{
    m_skin = skin;
}

void AnimRigConverter::postProcess()
{
    ComponentConverter::postProcess();

    m_rigFileName = m_ownner->m_config->m_exportFolder + m_name + "_rig.havok";

#ifdef HAVOK_COMPILE
    extern const char* g_humanBodyNames[];
    //if we have a skin rig data
    //we should also write the rig data to a specific havok hkt file
    //here we split the skin and skeleton file
    //as we can share the same rig with difference skin model.
    LOGD("Write rig file: %s.", m_rigFileName.c_str());
    hkaSkeleton* skeleton = (hkaSkeleton*)m_skin->m_rig;
    for(int i=0; i<skeleton->m_bones.getSize(); ++i)
    {
        const hkaBone& bone = skeleton->m_bones[i];
        m_boneNames.push_back(bone.m_name.cString());
        const std::string& boneName = m_boneNames[i];
        int index = findBodyPart(boneName, g_body_names_0);
        if(index < 0) continue;
        if(m_bodyPart[index] >= 0) continue; //already found.
        m_bodyPart[index] = i;
        LOGD("find body part %s --> %s", boneName.c_str(), g_humanBodyNames[index]);
    }

    {
        hkPackfileWriter::Options options;
        options.m_writeMetaInfo = false;
        hkOstream ostream(m_rigFileName.c_str());
        hkBinaryPackfileWriter writer;
        writer.setContents(skeleton, hkaSkeleton::staticClass());
        if(writer.save(ostream.getStreamWriter(), options) != HK_SUCCESS)
            g_hc_config->m_error.add_error("%s write error.", BX_FUNCTION);
    }
#endif

    {
        m_rigJson = m_ownner->m_config->m_exportFolder + m_name + ".rig";
        writeRig(m_rigJson);
    }
}

jsonxx::Object AnimRigConverter::serializeToJson() const
{
    jsonxx::Object rigObject;
    rigObject << "name" << getResourceName();
    rigObject << "type" << getTypeName();
    return rigObject;
}

int AnimRigConverter::findBodyPart( const std::string& boneName, const char** arrayBones )
{
    std::string boneNameLower = boneName;
    toLower(boneNameLower);
    for (int i=0; i<kBodyPartMax; ++i)
    {
        std::string::size_type pos = boneNameLower.find(arrayBones[i]);
        if(pos != std::string::npos)
            return i;
    }
    return -1;
}

void AnimRigConverter::writeRig( const std::string& fileName )
{
    std::ofstream s(fileName);
    if(!s.good())
    {
        g_hc_config->m_error.add_error("%s to %s IO error.", __FUNCTION__, fileName.c_str());
        return;
    }
    s << getRigJson().json();
}

jsonxx::Object AnimRigConverter::getRigJson() const
{
    extern const char* g_humanBodyNames[];

    jsonxx::Object obj;
    obj << "name" << getResourceName();
    obj << "type" << getTypeName();
    obj << "havok_file" << m_rigFileName;
    obj << "joint_num" << m_boneNames.size();
    jsonxx::Array joints;
    for (size_t i=0; i<m_boneNames.size(); ++i)
    {
        joints << m_boneNames[i];
    }
    obj << "joints" << joints;

    jsonxx::Object body;
    for (uint32_t i=0; i<kBodyPartMax; ++i)
    {
        int index = m_bodyPart[i];
        if(index >= 0)
        {
            std::string boneName = m_boneNames[index];
            std::string bodyName = g_humanBodyNames[i];
            body << bodyName << boneName;
        }
    }
    obj << "human_body" << body;

#ifdef HAVOK_COMPILE
    jsonxx::Array attachments;
    float m[16];
    LOGI("attachment num = %d", m_skin->m_attachments.size());
    for(unsigned i=0; i<m_skin->m_attachments.size(); ++i)
    {
        const hkaBoneAttachment* ba = m_skin->m_attachments[i];
        jsonxx::Object attachment;
        attachment << "name" << std::string(ba->m_name.cString());
        attachment << "bone" << (int)ba->m_boneIndex;
        jsonxx::Array matrixArray;
        transform_matrix(m, ba->m_boneFromAttachment);
        for (int i = 0; i < 16; ++i)
        {
            matrixArray << m[i];
        }
        attachment << "transform" << matrixArray;
        attachments << attachment;
    }
    obj << "attachments" << attachments;
#endif
    return obj;
}
