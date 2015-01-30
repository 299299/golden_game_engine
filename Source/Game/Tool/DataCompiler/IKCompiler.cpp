#include "IKCompiler.h"
#include "AnimRig.h"

static const char* raycast_type_names[] =
{
    "physics", "graphics", 0
};
static const char* left_right_names[] =
{
    "left", "right", 0
};

bool LookIKCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    LookAtResource lookat;
    memset(&lookat, 0x00, sizeof(lookat));

    vec3_make(lookat.m_fwdLS, 0, 0, 1);
    json_to_floats(root, "forward_ls", lookat.m_fwdLS, 3);

    lookat.m_lookAtLimit = json_to_float(root, "lookat_limit", 3.1415926f/4.0f);
    lookat.m_gain = json_to_float(root, "gain", 0.05f);
    lookat.m_targetGain =  json_to_float(root, "target_gain", 0.2f);

    const std::string& rigFile = root.get<std::string>("rig");
    lookat.m_rigName = stringid_caculate(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &lookat, sizeof(lookat));
}

bool ReachIKCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    ReachResource reach;
    memset(&reach, 0x00, sizeof(reach));

    vec3_make(reach.m_elbowAxis, 0, 1, 0);
    json_to_floats(root, "elbow_axis", reach.m_elbowAxis, 3);

    reach.m_hingeLimitAngle[0] = 0;
    reach.m_hingeLimitAngle[1] = 180;

    json_to_floats(root, "hinge_limit_angle", reach.m_hingeLimitAngle, 2);

    reach.m_reachGain = json_to_float(root, "reach_gain", 0.3f);
    reach.m_leaveGain = json_to_float(root, "leave_gain", 0.19f);
    reach.m_moveGain = json_to_float(root, "move_gain", 0.085f);
    reach.m_targetGain = json_to_float(root, "target_gain", 0.2f);
    reach.m_index = json_to_enum(root, "hand", left_right_names);

    const std::string& rigFile = root.get<std::string>("rig");
    reach.m_rigName = stringid_caculate(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &reach, sizeof(reach));
}

bool FootIKCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    FootResource foot;
    memset(&foot, 0x00, sizeof(foot));

    vec3_make(foot.m_leftKneeAxisLS, 0, 0, 1);
    vec3_make(foot.m_rightKneeAxisLS, 0, 0, 1);
    vec3_make(foot.m_footEndLS, 0, 0, 0.2f);

    json_to_floats(root, "left_knee_axis", foot.m_leftKneeAxisLS, 3);
    json_to_floats(root, "right_knee_axis", foot.m_rightKneeAxisLS, 3);
    json_to_floats(root, "foot_end_ls", foot.m_footEndLS, 3);

    foot.m_orignalGroundHeightMS = json_to_float(root, "orignal_ground_height_ms");
    foot.m_minAnkleHeightMS = json_to_float(root, "min_ankle_height_ms");
    foot.m_maxAnkleHeightMS = json_to_float(root, "max_ankle_height_ms");
    foot.m_footPlantedAnkleHeightMS = json_to_float(root, "foot_planted_ankle_height_ms");
    foot.m_footRaisedAnkleHeightMS = json_to_float(root, "foot_raised_ankle_height_ms");
    foot.m_cosineMaxKneeAngle = json_to_float(root, "max_consine_knee_angle", 180);
    foot.m_cosineMinKneeAngle = json_to_float(root, "min_consine_knee_angle", 0);
    foot.m_raycastDistanceUp = json_to_float(root, "raycast_dis_up", 0.5f);
    foot.m_raycastDistanceDown = json_to_float(root, "raycast_dis_down", 0.8f);
    foot.m_raycastCollisionLayer = json_to_stringid(root, "raycast_layer");
    foot.m_groundAscendingGain =  json_to_float(root, "ground_ascending_gain", 0.35f);
    foot.m_groundDescendingGain =  json_to_float(root, "ground_descending_gain", 0.6f);
    foot.m_standAscendingGain =  json_to_float(root, "ground_ascending_gain", 0.6f);
    foot.m_footPlantedGain =  json_to_float(root, "foot_planted_gain", 1.0f);
    foot.m_footRaisedGain =  json_to_float(root, "foot_raised_gain", 0.85f);
    foot.m_footOnOffGain =  json_to_float(root, "foot_onoff_gain", 0.2f);
    foot.m_footUnLockGain =  json_to_float(root, "foot_unlock_gain", 0.85f);
    foot.m_pelvisFeedback =  json_to_float(root, "pelvis_feedback", 0.1f);
    foot.m_pelvisUpDownBias =  json_to_float(root, "pelvis_updown_bias", 0.95f);
    foot.m_raycastType = json_to_enum(root, "raycast_type", raycast_type_names, 0);

    const std::string& rigFile = root.get<std::string>("rig");
    foot.m_rigName = stringid_caculate(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &foot, sizeof(foot));
}
