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
    if(root.has<jsonxx::Array>("forward-ls"))
    {
        json_to_floats(root.get<jsonxx::Array>("forward-ls"), lookat.m_fwdLS, 3);
    }
    lookat.m_lookAtLimit = root.get<float>("lookat-limit", 3.1415926f/4.0f);
    lookat.m_gain = root.get<float>("gain", 0.05f);
    lookat.m_targetGain = root.get<float>("target-gain", 0.2f);

    const std::string& rigFile = root.get<std::string>("rig");
    lookat.m_rigName = StringId(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &lookat, sizeof(lookat));
}

bool ReachIKCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    ReachResource reach;
    memset(&reach, 0x00, sizeof(reach));

    vec3_make(reach.m_elbowAxis, 0, 1, 0);
    if(root.has<jsonxx::Array>("elbow-axis"))
    {
        json_to_floats(root.get<jsonxx::Array>("elbow-axis"), reach.m_elbowAxis, 3);
    }

    reach.m_hingeLimitAngle[0] = 0;
    reach.m_hingeLimitAngle[1] = 180;

    if(root.has<jsonxx::Array>("hinge-limit-angle"))
    {
        json_to_floats(root.get<jsonxx::Array>("hinge-limit-angle"), reach.m_hingeLimitAngle, 2);
    }

    reach.m_reachGain = root.get<float>("reach-gain", 0.3f);
    reach.m_leaveGain = root.get<float>("leave-gain", 0.19f);
    reach.m_moveGain = root.get<float>("move-gain", 0.085f);
    reach.m_targetGain = root.get<float>("target-gain", 0.2f);
    reach.m_index = find_enum_index(root.get<std::string>("hand").c_str(), left_right_names);

    const std::string& rigFile = root.get<std::string>("rig");
    reach.m_rigName = StringId(rigFile.c_str());
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

    if(root.has<jsonxx::Array>("left-knee-axis"))
    {
        json_to_floats(root.get<jsonxx::Array>("left-knee-axis"), foot.m_leftKneeAxisLS, 3);
    }
    if(root.has<jsonxx::Array>("right-knee-axis"))
    {
        json_to_floats(root.get<jsonxx::Array>("right-knee-axis"), foot.m_rightKneeAxisLS, 3);
    }
    if(root.has<jsonxx::Array>("foot-end-ls"))
    {
        json_to_floats(root.get<jsonxx::Array>("foot-end-ls"), foot.m_footEndLS, 3);
    }

    foot.m_orignalGroundHeightMS = root.get<float>("orignal-ground-height-ms");
    foot.m_minAnkleHeightMS = root.get<float>("min-ankle-height-ms");
    foot.m_maxAnkleHeightMS = root.get<float>("max-ankle-height-ms");
    foot.m_footPlantedAnkleHeightMS = root.get<float>("foot-planted-ankle-height-ms");
    foot.m_footRaisedAnkleHeightMS = root.get<float>("foot-raised-ankle-height-ms");
    foot.m_cosineMaxKneeAngle = root.get<float>("max-consine-knee-angle", 180);
    foot.m_cosineMinKneeAngle = root.get<float>("min-consine-knee-angle", 0);
    foot.m_raycastDistanceUp = root.get<float>("raycast-dis-up", 0.5f);
    foot.m_raycastDistanceDown = root.get<float>("raycast-dis-down", 0.8f);
    foot.m_raycastCollisionLayer = StringId(root.get<std::string>("raycast-layer").c_str());
    foot.m_groundAscendingGain =  root.get<float>("ground-ascending-gain", 0.35f);
    foot.m_groundDescendingGain =  root.get<float>("ground-descending-gain", 0.6f);
    foot.m_standAscendingGain =  root.get<float>("ground-ascending-gain", 0.6f);
    foot.m_footPlantedGain =  root.get<float>("foot_planted-gain", 1.0f);
    foot.m_footRaisedGain =  root.get<float>("foot-raised-gain", 0.85f);
    foot.m_footOnOffGain =  root.get<float>("foot-onoff-gain", 0.2f);
    foot.m_footUnLockGain =  root.get<float>("foot-unlock-gain", 0.85f);
    foot.m_pelvisFeedback =  root.get<float>("pelvis-feedback", 0.1f);
    foot.m_pelvisUpDownBias =  root.get<float>("pelvis-updown-bias", 0.95f);
    foot.m_raycastType = find_enum_index(root.get<std::string>("raycast-type").c_str(), raycast_type_names);

    const std::string& rigFile = root.get<std::string>("rig");
    foot.m_rigName = StringId(rigFile.c_str());
    addDependency("rig", name_to_file_path(rigFile, AnimRig::get_name()));

    return write_file(m_output, &foot, sizeof(foot));
}
