#include "IKCompiler.h"
#include "DC_Utils.h"
#include "AnimRig.h"

static const char* raycast_type_names[] =
{
    "physics", "graphics", 0
};
static const char* left_right_names[] = 
{
    "left", "right", 0
};

bool LookIKCompiler::readJSON( const JsonValue& root )
{
    __super::readJSON(root);
    LookAtResource lookat;
    memset(&lookat, 0x00, sizeof(lookat));

    vec3_make(lookat.m_fwdLS, 0, 0, 1);
    JSON_GetFloats(root.GetValue("forward-ls"), lookat.m_fwdLS, 3);

    lookat.m_lookAtLimit = JSON_GetFloat(root.GetValue("lookat-limit"), 3.1415926f / 4.0f);
    lookat.m_gain = JSON_GetFloat(root.GetValue("gain"), 0.05f);
    lookat.m_targetGain = JSON_GetFloat(root.GetValue("target-gain"),  0.2f);

    std::string rigFile = JSON_GetString(root.GetValue("rig"));
    lookat.m_rigName = StringId(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &lookat, sizeof(lookat));
}

bool ReachIKCompiler::readJSON( const JsonValue& root )
{
    __super::readJSON(root);
    ReachResource reach;
    memset(&reach, 0x00, sizeof(reach));

    vec3_make(reach.m_elbowAxis, 0, 1, 0);
    JSON_GetFloats(root.GetValue("elbow_axis"), reach.m_elbowAxis, 3);

    reach.m_hingeLimitAngle[0] = 0;
    reach.m_hingeLimitAngle[1] = 180;

    JSON_GetFloats(root.GetValue("hinge_limit_angle"), reach.m_hingeLimitAngle, 2);

    reach.m_reachGain = JSON_GetFloat(root.GetValue("reach_gain"),  0.3f);
    reach.m_leaveGain = JSON_GetFloat(root.GetValue("leave_gain"), 0.19f);
    reach.m_moveGain = JSON_GetFloat(root.GetValue("move_gain"), 0.085f);
    reach.m_targetGain = JSON_GetFloat(root.GetValue("target_gain"),  0.2f);
    reach.m_index = JSON_GetEnum(root.GetValue("hand"), left_right_names);

    std::string rigFile = JSON_GetString(root.GetValue("rig"));
    reach.m_rigName = StringId(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &reach, sizeof(reach));
}

bool FootIKCompiler::readJSON( const JsonValue& root )
{
    __super::readJSON(root);
    FootResource foot;
    memset(&foot, 0x00, sizeof(foot));

    vec3_make(foot.m_leftKneeAxisLS, 0, 0, 1);
    vec3_make(foot.m_rightKneeAxisLS, 0, 0, 1);
    vec3_make(foot.m_footEndLS, 0, 0, 0.2f);

    JSON_GetFloats(root.GetValue("left_knee_axis"), foot.m_leftKneeAxisLS, 3);
    JSON_GetFloats(root.GetValue("right_knee_axis"), foot.m_rightKneeAxisLS, 3);
    JSON_GetFloats(root.GetValue("foot_end_ls"), foot.m_footEndLS, 3);

    foot.m_orignalGroundHeightMS = JSON_GetFloat(root.GetValue("orginal_ground_height_ms"));
    foot.m_minAnkleHeightMS = JSON_GetFloat(root.GetValue("min_ankle_height_ms"));
    foot.m_maxAnkleHeightMS = JSON_GetFloat(root.GetValue("max_ankle_height_ms"));
    foot.m_footPlantedAnkleHeightMS = JSON_GetFloat(root.GetValue("foot_planted_ankle_height_ms"));
    foot.m_footRaisedAnkleHeightMS = JSON_GetFloat(root.GetValue("foot_raised_ankle_height_ms"));
    foot.m_cosineMaxKneeAngle = JSON_GetFloat(root.GetValue("max_consine_knee_angle"), 180);
    foot.m_cosineMinKneeAngle = JSON_GetFloat(root.GetValue("min_consine_knee_angle"), 0);
    foot.m_raycastDistanceUp = JSON_GetFloat(root.GetValue("raycast_dis_up"), 0.5f);
    foot.m_raycastDistanceDown = JSON_GetFloat(root.GetValue("raycast_dis_down"), 0.8f);
    foot.m_raycastCollisionLayer = JSON_GetStringId(root.GetValue("raycast_layer"), StringId("raycast"));
    foot.m_groundAscendingGain = JSON_GetFloat(root.GetValue("ground_ascending_gain"), 0.35f);
    foot.m_groundDescendingGain = JSON_GetFloat(root.GetValue("ground_descending_gain"), 0.6f);
    foot.m_standAscendingGain = JSON_GetFloat(root.GetValue("ground_ascending_gain"), 0.6f);
    foot.m_footPlantedGain = JSON_GetFloat(root.GetValue("foot_planted_gain"), 1.0f);
    foot.m_footRaisedGain = JSON_GetFloat(root.GetValue("foot_raised_gain"), 0.85f);
    foot.m_footOnOffGain = JSON_GetFloat(root.GetValue("foot_onoff_gain"), 0.2f);
    foot.m_footUnLockGain = JSON_GetFloat(root.GetValue("foot_unlock_gain"), 0.85f);
    foot.m_pelvisFeedback = JSON_GetFloat(root.GetValue("pelvis_feedback"), 0.1f);
    foot.m_pelvisUpDownBias = JSON_GetFloat(root.GetValue("pelvis_updown_bias"), 0.95f);
    foot.m_raycastType = JSON_GetEnum(root.GetValue("raycast_type"), raycast_type_names);

    std::string rigFile = JSON_GetString(root.GetValue("rig"));
    foot.m_rigName = StringId(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &foot, sizeof(foot));
}
