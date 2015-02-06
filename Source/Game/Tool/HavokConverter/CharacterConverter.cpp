#include "CharacterConverter.h"
#include "ModelConverter.h"
#include "AnimRigConverter.h"
#include "AnimRig.h"

CharacterConverter::CharacterConverter()
    :m_ac(0)
    ,m_skin(0)
{

}

CharacterConverter::~CharacterConverter()
{
    SAFE_DELETE(m_skin);
}

void CharacterConverter::process(void* data)
{
    process((hkaAnimationContainer*)data);
}

void CharacterConverter::process(hkaAnimationContainer* ac)
{
    m_ac = ac;
#ifdef HAVOK_COMPILE
    if(ac->m_skeletons.isEmpty())
    {
        g_hc_config->m_error.add_error("skinning do not found skeleton!");
        return;
    }
    collectRigSkinData(ac->m_skeletons[0]);
    ModelConverter* mc = new ModelConverter(this);
    mc->m_type = kModelSkinning;
    mc->m_node = findNode(EngineNames::MODEL);
    mc->setName(m_name);
    mc->process((void*)m_skin, 1);
    m_components.push_back(mc);
    AnimRigConverter* anic = new AnimRigConverter(this);
    anic->m_node = findNode(EngineNames::ANIMATION_RIG);
    anic->setName(m_name);
    anic->process((void*)m_skin);
    m_components.push_back(anic);
#endif
}

void CharacterConverter::collectRigSkinData(hkaSkeleton* rig)
{
#ifdef HAVOK_COMPILE
    if(rig->m_bones.isEmpty())
    {
        LOGE("warning rig bones is empty.");
        return;
    }

    m_skin = new RigSkinData;
    m_skin->m_rig = rig;
    LOGD("collecting rig = %s ", rig->m_name.cString());

    //collect meshbindings
    for (int j = 0; j < m_ac->m_skins.getSize(); ++j)
    {
        hkaMeshBinding* skin = m_ac->m_skins[j];
        if(skin->m_skeleton == rig)
            m_skin->m_skins.push_back(skin);
        LOGD("add mesh binding = %s ", skin->m_name.cString());
    }

    //collect bone attachments
    for (int j = 0; j < m_ac->m_attachments.getSize(); ++j)
    {
        hkaBoneAttachment* attachment = m_ac->m_attachments[j];
        if(attachment->m_originalSkeletonName == rig->m_name)
        {
            m_skin->m_attachments.push_back(attachment);
        }
    }
#endif
}

jsonxx::Object CharacterConverter::serializeToJson() const
{
    return ActorConverter::serializeToJson();
}
