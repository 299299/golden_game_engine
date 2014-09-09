#pragma once
#include "StringId.h"
#include "Prerequisites.h"

class hkaSkeleton;
class hkaMirroredSkeleton;
class hkaPose;
class hkaAnimatedSkeleton;
struct AnimationTrigger;

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
    float               m_transform[16];
    StringId            m_name;
    int                 m_boneIndex;
};

ENGINE_NATIVE_ALIGN struct AnimRig
{
    DECLARE_RESOURCE(rig);

    int  findJointIndex(const StringId& jointName);
    void createMirrorSkeleton();

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

struct AnimRigInstance
{
    const AnimRig*                  m_resource;
    hkaPose*                        m_pose;
    hkaAnimatedSkeleton*            m_skeleton;
    ID                              m_id;

    void init(const void* resource);
    void setTransform(const hkQsTransform& t) {};
    void setEnabled(bool bEnable) {};

    void destroy();
    void reset();
    void getRootmotion(float dt, hkQsTransform& motionOut);
    int  getTriggers(int layer, float dt, AnimationTrigger* outTriggers);
    void updateLocalClock(float dt);
    void fireTransition(const StringId& t, int layerId = -1);
    void updateLayers(float dt);
    inline hkaPose& getPose() { return *m_pose; };
    void testAnimation(const char* animFile);
};

void* load_resource_anim_rig(const char* data, uint32_t size);
void  destroy_resource_anim_rig(void * resource);
