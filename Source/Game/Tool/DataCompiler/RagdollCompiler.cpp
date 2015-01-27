#include "RagdollCompiler.h"

RagdollCompiler::RagdollCompiler()
{

}

RagdollCompiler::~RagdollCompiler()
{

}

bool RagdollCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    const std::string& havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        g_config->m_error.add_error("%s can not find havok file [%s]", BX_FUNCTION, havokFile.c_str());
        return false;
    }

    uint32_t havokOffset = sizeof(RagdollResource);
    uint32_t memSize = havokOffset + havokReader.m_size;
    MemoryBuffer mem(memSize);
    memcpy(mem.m_buf + havokOffset, havokReader.m_buf, havokReader.m_size);

    RagdollResource* ragdoll = (RagdollResource*)mem.m_buf;
    ragdoll->m_velocityGain = json_to_float(root, "velocity_gain", 0.6f);
    ragdoll->m_positionGain = json_to_float(root, "position_gain", 0.33f);
    ragdoll->m_positionMaxLinearVelocity = json_to_float(root, "position_max_linear_velocity", 1.4f);
    ragdoll->m_positionMaxAngularVelocity = json_to_float(root, "position_max_angular_velocity", 1.8f);
    ragdoll->m_snapGain = json_to_float(root, "snap_gain", 0.1f);
    ragdoll->m_snapMaxLinearVelocity = json_to_float(root, "snap_max_linear_velocity", 0.3f);
    ragdoll->m_snapMaxAngularVelocity = json_to_float(root, "snap_max_angular_velocity", 0.3f);
    ragdoll->m_snapMaxLinearDistance = json_to_float(root, "snap_max_linear_distance", 0.3f);
    ragdoll->m_snapMaxAngularDistance = json_to_float(root, "snap_max_angular_distance", 0.1f);
    ragdoll->m_hasFeedBack = root.get<bool>("has_feed_back", true);
    ragdoll->m_ragdollFeedback = json_to_float(root, "ragdoll_feed_back", 1.0f);
    ragdoll->m_hierarchyGain = json_to_float(root, "hierarchy_gain", 0.17f);
    ragdoll->m_dampVelocity = json_to_float(root, "damp_velocity", 0.0f);
    ragdoll->m_accelerationGain = json_to_float(root, "acceleration_gain", 1.0f);
    ragdoll->m_fixLegs = root.get<bool>("fix-legs", true);
    ragdoll->m_leftLeg = StringId(root.get<std::string>("left_leg").c_str());
    ragdoll->m_rightLeg = StringId(root.get<std::string>("right_leg").c_str());
    ragdoll->m_keyframeLayer = StringId(root.get<std::string>("keyframe_layer", "ragdoll_keyframe").c_str());
    ragdoll->m_dynamicLayer = StringId(root.get<std::string>("dynamic_layer", "ragdoll_dynamic").c_str());
    return write_file(m_output, mem.m_buf, memSize);
}