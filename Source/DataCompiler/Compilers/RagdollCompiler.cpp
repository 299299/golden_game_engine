#include "RagdollCompiler.h"
#include "DC_Utils.h"

RagdollCompiler::RagdollCompiler()
{

}

RagdollCompiler::~RagdollCompiler()
{

}

bool RagdollCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    std::string havokFile = JSON_GetString(root.GetValue("havok_file"));
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        addError(__FUNCTION__ "can not find havok file [%s]", havokFile.c_str());
        return false;
    }
    
    uint32_t havokOffset = sizeof(RagdollResource);
    uint32_t memSize = havokOffset + havokReader.m_size;
    MemoryBuffer mem(memSize);
    memcpy(mem.m_buf + havokOffset, havokReader.m_buf, havokReader.m_size);

    RagdollResource* ragdoll = (RagdollResource*)mem.m_buf;
    ragdoll->m_velocityGain = JSON_GetFloat(root.GetValue("velocity_gain"), 0.6f);
    ragdoll->m_positionGain = JSON_GetFloat(root.GetValue("position_gain"), 0.33f);
    ragdoll->m_positionMaxLinearVelocity = JSON_GetFloat(root.GetValue("position_max_linear_velocity"), 1.4f);
    ragdoll->m_positionMaxAngularVelocity = JSON_GetFloat(root.GetValue("position_max_angular_velocity"), 1.8f);
    ragdoll->m_snapGain = JSON_GetFloat(root.GetValue("snap_gain"), 0.1f);
    ragdoll->m_snapMaxLinearVelocity = JSON_GetFloat(root.GetValue("snap_max_linear_velocity"), 0.3f);
    ragdoll->m_snapMaxAngularVelocity = JSON_GetFloat(root.GetValue("snap_max_angular_velocity"), 0.3f);
    ragdoll->m_snapMaxLinearDistance = JSON_GetFloat(root.GetValue("snap_max_linear_distance"), 0.3f);
    ragdoll->m_snapMaxAngularDistance = JSON_GetFloat(root.GetValue("snap_max_angular_distance"), 0.1f);
    ragdoll->m_hasFeedBack = JSON_GetBool(root.GetValue("has_feed_back"));
    ragdoll->m_ragdollFeedback = JSON_GetFloat(root.GetValue("ragdoll_feed_back"), 1.0f);
    ragdoll->m_hierarchyGain = JSON_GetFloat(root.GetValue("hierarchy_gain"), 0.17f);
    ragdoll->m_dampVelocity = JSON_GetFloat(root.GetValue("damp_velocity"), 0.0f);
    ragdoll->m_accelerationGain = JSON_GetFloat(root.GetValue("acceleration_gain"), 1.0f);
    ragdoll->m_fixLegs = JSON_GetBool(root.GetValue("fix_legs"), true); 
    ragdoll->m_leftLeg = JSON_GetStringId(root.GetValue("left_leg"));
    ragdoll->m_rightLeg = JSON_GetStringId(root.GetValue("right_leg"));
    ragdoll->m_keyframeLayer = JSON_GetStringId(root.GetValue("keyframe_layer"), StringId("ragdoll_keyframe"));
    ragdoll->m_dynamicLayer = JSON_GetStringId(root.GetValue("dynamic_layer"), StringId("ragdoll_dynamic"));
    return write_file(m_output, mem.m_buf, memSize);
}