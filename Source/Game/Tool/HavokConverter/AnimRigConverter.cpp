#include "AnimRigConverter.h"
#include "ModelConverter.h"
#include "ActorConverter.h"

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
    __super::postProcess();

    m_rigFileName = m_ownner->m_config->m_exportFolder + m_name + "_rig.havok";
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
            g_config->m_error.add_error(__FUNCTION__" write error.");
    }
    
}

jsonxx::Object AnimRigConverter::serializeToJson() const
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
    fillAttributes(obj);
    return obj;
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

void AnimRigConverter::fillAttributes( jsonxx::Object& object ) const
{
	if(!m_node) return;
	const hkxAttributeGroup* group = m_node->findAttributeGroupByName(ENGINE_ATTRIBUTES);
	if(!group) return;
	fill_object_attributes(object, group);
	const char* animSetName = 0;
	hkResult result = group->getStringValue("anim_set", true, animSetName);
	if(result != HK_SUCCESS) return;
    //HACK HERE!
    std::string animSetFile("../pipeline/bones/");
    animSetFile += animSetName;
    animSetFile += "_animset.json";
	FileReader reader(animSetFile.c_str());
	if (!reader.m_size) return;
	jsonxx::Value obj;
	if(!obj.parse(reader.m_buf)) 
	{
		g_config->m_error.add_error("anim-set %s json parse error.", animSetFile.c_str());
		return;
	}
	object<<"animation-set"<<obj;
}
