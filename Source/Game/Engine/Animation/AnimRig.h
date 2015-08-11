#pragma once
#include "StringId.h"
#include "Prerequisites.h"
#include "DataDef.h"

class   hkaSkeleton;
class   hkaMirroredSkeleton;
class   hkaPose;
class   hkaAnimatedSkeleton;
struct  AnimationTrigger;
class   hkaDefaultAnimationControl;
struct  Animation;
struct  hk_anim_ctrl;
struct  AnimationEvent;

ENGINE_NATIVE_ALIGN(struct) BoneAttachment
{
    ENGINE_NATIVE_ALIGN(float m_bone_from_attachment[16]);
    StringId            m_name;
    int                 m_bone_index;
};

ENGINE_NATIVE_ALIGN(struct) AnimRig
{
    int  find_joint_index(StringId jointName) const;
    void create_mirrored_skeleton();

    int                             m_human_joint_indices[kBodyPartMax];
    hkaSkeleton*                    m_skeleton;
    hkaMirroredSkeleton*            m_mirrored_skeleton;

    uint32_t                        m_joint_name_offset;
    uint32_t                        m_attachment_offset;
    uint32_t                        m_havok_data_offset;
    uint32_t                        m_havok_data_size;

    uint16_t                        m_num_joints;
    uint8_t                         m_num_attchments;
    bool                            m_mirrored;
};

ENGINE_NATIVE_ALIGN(struct) AnimRigInstance
{
    const AnimRig*                  m_resource;
    hkaPose*                        m_pose;
    hkaAnimatedSkeleton*            m_skeleton;
    float*                          m_attachment_transforms;
    char*                           m_blob;
    ActorId32                       m_actor;

    void init(const void* resource, ActorId32 actor);
    void destroy();
    void update(float dt);
    void update_attachment(const hkQsTransform& worldFromModel);
    void test_animation(const char* name);
    int  collect_event(AnimationEvent* events, float dt);
};

void* load_resource_anim_rig(void*, uint32_t);
void destroy_resource_anim_rig(void *);

