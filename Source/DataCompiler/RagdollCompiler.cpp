#include "RagdollCompiler.h"

RagdollCompiler::RagdollCompiler()
{

}

RagdollCompiler::~RagdollCompiler()
{

}

bool RagdollCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    std::string havokFile = JSON_GetString(root.GetValue("havok-file"));
    char* havokData = 0;
    uint32_t havokFileSize = read_file(havokFile.c_str(), &havokData);
    if(havokFileSize < 16)
    {
        addError(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
        return false;
    }
    
    uint32_t havokOffset = sizeof(RagdollResource);
    uint32_t memSize = havokOffset + havokFileSize;
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    memcpy(p + havokOffset, havokData, havokFileSize);
    free(havokData);
    RagdollResource* ragdoll = (RagdollResource*)p;
    ragdoll->m_velocityGain = JSON_GetFloat(root.GetValue("velocity-gain"), 0.6f);
    ragdoll->m_positionGain = JSON_GetFloat(root.GetValue("position-gain"), 0.33f);
    ragdoll->m_positionMaxLinearVelocity = JSON_GetFloat(root.GetValue("position-max-linear-velocity"), 1.4f);
    ragdoll->m_positionMaxAngularVelocity = JSON_GetFloat(root.GetValue("position-max-angular-velocity"), 1.8f);
    ragdoll->m_snapGain = JSON_GetFloat(root.GetValue("snap-gain"), 0.1f);
    ragdoll->m_snapMaxLinearVelocity = JSON_GetFloat(root.GetValue("snap-max-linear-velocity"), 0.3f);
    ragdoll->m_snapMaxAngularVelocity = JSON_GetFloat(root.GetValue("snap-max-angular-velocity"), 0.3f);
    ragdoll->m_snapMaxLinearDistance = JSON_GetFloat(root.GetValue("snap-max-linear-distance"), 0.3f);
    ragdoll->m_snapMaxAngularDistance = JSON_GetFloat(root.GetValue("snap-max-angular-distance"), 0.1f);
    ragdoll->m_hasFeedBack = JSON_GetBool(root.GetValue("has-feed-back"));
    ragdoll->m_ragdollFeedback = JSON_GetFloat(root.GetValue("ragdoll-feed-back"), 1.0f);
    ragdoll->m_hierarchyGain = JSON_GetFloat(root.GetValue("hierarchy-gain"), 0.17f);
    ragdoll->m_dampVelocity = JSON_GetFloat(root.GetValue("damp-velocity"), 0.0f);
    ragdoll->m_accelerationGain = JSON_GetFloat(root.GetValue("acceleration-gain"), 1.0f);
    ragdoll->m_fixLegs = JSON_GetBool(root.GetValue("fix-legs"), true); 
    ragdoll->m_leftLeg = JSON_GetStringId(root.GetValue("left-leg"));
    ragdoll->m_rightLeg = JSON_GetStringId(root.GetValue("right-leg"));
    bool bRet = write_file(m_output, p, memSize);
    free(p);
    return bRet;
}