#include "RagdollCompiler.h"

RagdollCompiler::RagdollCompiler()
{

}

RagdollCompiler::~RagdollCompiler()
{

}

bool RagdollCompiler::readJSON(const jsonxx::Object& root)
{
    __super::readJSON(root);
    const std::string& havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        g_config->m_error.add_error(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
        return false;
    }
    
    uint32_t havokOffset = sizeof(RagdollResource);
    uint32_t memSize = havokOffset + havokReader.m_size;
    MemoryBuffer mem(memSize);
    memcpy(mem.m_buf + havokOffset, havokReader.m_buf, havokReader.m_size);

    RagdollResource* ragdoll = (RagdollResource*)mem.m_buf;
    ragdoll->m_velocityGain = root.get<float>("velocity-gain", 0.6f);
    ragdoll->m_positionGain = root.get<float>("position-gain", 0.33f);
    ragdoll->m_positionMaxLinearVelocity = root.get<float>("position-max-linear-velocity", 1.4f);
    ragdoll->m_positionMaxAngularVelocity = root.get<float>("position-max-angular-velocity", 1.8f);
    ragdoll->m_snapGain = root.get<float>("snap-gain", 0.1f);
    ragdoll->m_snapMaxLinearVelocity = root.get<float>("snap-max-linear-velocity", 0.3f);
    ragdoll->m_snapMaxAngularVelocity = root.get<float>("snap-max-angular-velocity", 0.3f);
    ragdoll->m_snapMaxLinearDistance = root.get<float>("snap-max-linear-distance", 0.3f);
    ragdoll->m_snapMaxAngularDistance = root.get<float>("snap-max-angular-distance", 0.1f);
    ragdoll->m_hasFeedBack = root.get<bool>("has-feed-back", true);
    ragdoll->m_ragdollFeedback = root.get<float>("ragdoll-feed-back", 1.0f);
    ragdoll->m_hierarchyGain = root.get<float>("hierarchy-gain", 0.17f);
    ragdoll->m_dampVelocity = root.get<float>("damp-velocity", 0.0f);
    ragdoll->m_accelerationGain = root.get<float>("acceleration-gain", 1.0f);
    ragdoll->m_fixLegs = root.get<bool>("fix-legs", true);
    ragdoll->m_leftLeg = StringId(root.get<std::string>("left-leg").c_str());
    ragdoll->m_rightLeg = StringId(root.get<std::string>("right-leg").c_str());
    ragdoll->m_keyframeLayer = StringId(root.get<std::string>("keyframe-layer", "ragdoll-keyframe").c_str());
    ragdoll->m_dynamicLayer = StringId(root.get<std::string>("dynamic-layer", "ragdoll-dynamic").c_str());
    return write_file(m_output, mem.m_buf, memSize);
}