#pragma once
#include "StringId.h"
#include "Prerequisites.h"
#include "Utils.h"

class   hkaSkeleton;
class   hkaMirroredSkeleton;
class   hkaPose;
class   hkaAnimatedSkeleton;
struct  AnimationTrigger;
class   hkaDefaultAnimationControl;
struct  Animation;
struct  hk_anim_ctrl;

enum HumanBodypart
{
    kBodyHead,
    kBodyNeck,
    kBodyShoulder_L,
    kBodyArm_L,
    kBodyForeArm_L,
    kBodyHand_L,
    kBodyShoulder_R,
    kBodyArm_R,
    kBodyForeArm_R,
    kBodyHand_R,
    kBodyHip,
    kBodyUpLeg_L,
    kBodyLeg_L,
    kBodyFoot_L,
    kBodyUpLeg_R,
    kBodyLeg_R,
    kBodyFoot_R,
    kBodyPartMax
};

enum EaseCurveType
{
	kEaseCurveSmooth,
	kEaseCurveLinear,
	kEaseCurveFast
};

enum MotionType
{
    kMotionDefault,
    kMotionIgnoreRotation,
    kMotionIgnoreTranslation,
    kMotionIgnoreAll
};

struct BoneAttachment
{
    float               m_boneFromAttachment[16];
    StringId            m_name;
    int                 m_boneIndex;
};

ENGINE_NATIVE_ALIGN struct AnimRig
{
    DECLARE_RESOURCE(rig);

    int  find_joint_index(const StringId& jointName);
    void create_mirrored_skeleton();
    void update_attachments(const float* world_pose);

    int                             m_humanJointIndices[kBodyPartMax];
    hkaSkeleton*                    m_skeleton;
    hkaMirroredSkeleton*            m_mirroredSkeleton;
    BoneAttachment*                 m_attachments;

    StringId*                       m_jointNames;
    uint32_t                        m_havokDataOffset;
    uint32_t                        m_havokDataSize;

    uint16_t                        m_jointNum;
    uint8_t                         m_attachNum;
    bool                            m_mirrored;
};

ENGINE_NATIVE_ALIGN struct AnimRigInstance
{
    CommandMachine                  m_animMachine;
    const AnimRig*                  m_resource;
    hkaPose*                        m_pose;
    hkaAnimatedSkeleton*            m_skeleton;
    float*                          m_attachmentTransforms;
    hk_anim_ctrl*                   m_controls;
    uint32_t                        m_numControls;

    void init(const void* resource);
    void destroy();
    void update(float dt);
    bool is_playing_animation() const;
    void update_attachments(const float* worldFromModel);
    hk_anim_ctrl* get_control(int index) const { return m_controls + index; };
    int find_control(const StringId& name) const;
    void easein_animation(const StringId& name, float blend_time, float time = 0.0f, int type = kEaseCurveSmooth);
    void easeout_animation(const StringId& name, float blend_time, float time = 0.0f, int type = kEaseCurveSmooth);
    void test_animation(const char* name);
}; 
