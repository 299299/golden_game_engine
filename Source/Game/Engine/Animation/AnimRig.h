#pragma once
#include "StringId.h"
#include "Prerequisites.h"

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

struct BoneAttachment
{
    float               m_boneFromAttachment[16];
    StringId            m_name;
    int                 m_boneIndex;
};

ENGINE_NATIVE_ALIGN(struct) AnimRig
{
    int  find_joint_index(StringId jointName) const;
    void create_mirrored_skeleton();

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
