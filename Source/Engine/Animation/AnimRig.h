#pragma once
#include "StringId.h"
#include "Prerequisites.h"

class hkaSkeleton;
class hkaMirroredSkeleton;
class hkaPose;
class hkaAnimatedSkeleton;
struct AnimationTrigger;
class hkaDefaultAnimationControl;

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
    const AnimRig*                  m_resource;
    hkaPose*                        m_pose;
    hkaAnimatedSkeleton*            m_skeleton;
    float*                          m_attachmentTransforms;

    void init(const void* resource);
    void destroy();
    void update_local_clock(float dt);
    void play_animation(const StringId& anim_name, bool bLoop, float fTime);
    bool is_playing_animation() const;
    void update_attachments(const float* worldFromModel);
};
