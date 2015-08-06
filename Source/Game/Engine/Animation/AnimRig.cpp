#include "AnimRig.h"
#include "Resource.h"
#include "Log.h"
#include "Animation.h"
#include "MemorySystem.h"
#include "MathDefs.h"
#include "Utils.h"
#include "AnimControl.h"
#include "Event.h"
#include <bx/fpumath.h>
#ifdef HAVOK_COMPILE
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Animation/Animation/Animation/ReferencePose/hkaReferencePoseAnimation.h>
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
#endif

#define ANIM_EVT_WEIGHT_THRESHOLD 0.1f
//------------------------------------------------------------------------------------------------
//          RESOURCE
//------------------------------------------------------------------------------------------------

void* load_resource_anim_rig(void* data, uint32_t size)
{
    AnimRig* rig = (AnimRig*)data;
    rig->m_skeleton = (hkaSkeleton*)load_havok_inplace(
        (char*)data + rig->m_havok_data_offset,
        rig->m_havok_data_size);
    if(rig->m_mirrored)
        rig->create_mirrored_skeleton();
    return rig;
}
void  destroy_resource_anim_rig(void * resource)
{
    AnimRig* rig = (AnimRig*)resource;
#ifdef HAVOK_COMPILE
    SAFE_REMOVEREF(rig->m_mirrored_skeleton);
#endif
    unload_havok_inplace((char*)resource + rig->m_havok_data_offset, rig->m_havok_data_size);
}

int AnimRig::find_joint_index(StringId jointName) const
{
    int num = m_num_joints;
    StringId* head = (StringId*)((char*)this + m_joint_name_offset);
    FIND_IN_ARRAY_RET(head, num, jointName);
}

void AnimRig::create_mirrored_skeleton()
{
#ifdef HAVOK_COMPILE
    hkArray<hkStringPtr> ltag;
    hkArray<hkStringPtr> rtag;
    ltag.pushBack( "EyeL" ); rtag.pushBack( "EyeR" );
    ltag.pushBack( " L " ); rtag.pushBack( " R " );
    ltag.pushBack( "L_" ); rtag.pushBack( "R_" );
    ltag.pushBack( "_L" ); rtag.pushBack( "_R" );
    ltag.pushBack( "-L-" ); rtag.pushBack( "-R-" );
    ltag.pushBack( "-LUp" ); rtag.pushBack( "-RUp" );
    ltag.pushBack( "Left" ); rtag.pushBack( "Right" );
    m_mirrored_skeleton = new hkaMirroredSkeleton( m_skeleton );
    m_mirrored_skeleton->computeBonePairingFromNames( ltag, rtag );
    hkQuaternion v_mir( -1.0f, 0.0f, 0.0f, 0.0f );
    m_mirrored_skeleton->setAllBoneInvariantsFromReferencePose( v_mir, 0.0f );
#endif
}


void AnimRigInstance::init( const void* resource , ActorId32 actor)
{
    ComponentInstanceData* data = (ComponentInstanceData*)resource;
    AnimRig* rig = (AnimRig*)data->m_resource;
    m_actor = actor;
    m_attachment_transforms = 0;
    m_resource = (const AnimRig*)rig;
#ifdef HAVOK_COMPILE
    const hkaSkeleton* skeleton = rig->m_skeleton;
    //uint32_t pose_mem_size = hkaPose::getRequiredMemorySize(skeleton);
    uint32_t pose_size = NATIVE_ALGIN_SIZE(sizeof(hkaPose));
    uint32_t mem_size = sizeof(hkaSkeleton) + pose_size;
    m_blob = COMMON_ALLOC(char, mem_size);
    char* offset = m_blob;
    m_skeleton = new(offset) hkaAnimatedSkeleton(skeleton);
    offset += sizeof(hkaAnimatedSkeleton);
    m_pose = new(offset) hkaPose(skeleton);
    m_pose->setToReferencePose();
    m_pose->syncAll();
    //m_skeleton->setReferencePoseWeightThreshold(0.0f);
#endif
}

void AnimRigInstance::destroy()
{
#ifdef HAVOK_COMPILE
    SAFE_DESTRUCTOR(m_pose, hkaPose);
    SAFE_DESTRUCTOR(m_skeleton, hkaAnimatedSkeleton);
#endif
    COMMON_DEALLOC(m_blob);
}

void AnimRigInstance::update(float dt)
{
#ifdef HAVOK_COMPILE
    m_skeleton->stepDeltaTime(dt);
#if 0
    for (int i=0; i<m_skeleton->getNumAnimationControls(); ++i)
    {
        hk_anim_ctrl* ac = (hk_anim_ctrl*)m_skeleton->getAnimationControl(i);
        if(ac->getEaseStatus() == hkaDefaultAnimationControl::EASED_OUT)
        {
            m_skeleton->removeAnimationControl(ac);
            ac->m_enabled = false;
        }
    }
#endif
#endif
}

void AnimRigInstance::update_attachment( const hkQsTransform& worldFromModel )
{
#ifdef HAVOK_COMPILE
    uint32_t num = m_resource->m_num_attchments;
    m_attachment_transforms = FRAME_ALLOC(float, num*16);
    float* t = m_attachment_transforms;
    const BoneAttachment* attachments = (const BoneAttachment*)((char*)m_resource + m_resource->m_attachment_offset);
    const hkArray<hkQsTransform>& poseInWorld = m_pose->getSyncedPoseModelSpace();
    for (uint32_t i=0; i<num; ++i)
    {
        const BoneAttachment& ba = attachments[i];
        hkQsTransform boneWS;
        boneWS.setMul(worldFromModel, poseInWorld[ba.m_bone_index]);
        hkMatrix4 worldFromBone; 
        worldFromBone.set(boneWS);
        hkMatrix4 boneFromAttachment;
        boneFromAttachment.set4x4ColumnMajor(ba.m_bone_from_attachment);
        hkMatrix4 worldFromAttachment; 
        worldFromAttachment.setMul(worldFromBone, boneFromAttachment);
        worldFromAttachment.get4x4ColumnMajor(t + i*16);
    }
#endif
}

void AnimRigInstance::test_animation(const char* name)
{
#ifdef HAVOK_COMPILE
    Animation* anim = FIND_RESOURCE(Animation, EngineTypes::ANIMATION, stringid_caculate(name));
    if(!anim) return;
    for(int i=0; i<m_skeleton->getNumAnimationControls(); ++i)
    {
        m_skeleton->removeAnimationControl(m_skeleton->getAnimationControl(i));
    }
    hk_anim_ctrl* ac = new hk_anim_ctrl(anim);
    ac->easeIn(0.0f);
    ac->setLocalTime(0.0f);
    m_skeleton->addAnimationControl(ac);
    m_skeleton->setReferencePoseWeightThreshold(0.0f);
    ac->m_enabled = true;
    ac->set_loop(true);
    ac->removeReference();
#endif
}

int AnimRigInstance::collect_event( AnimationEvent* events )
{
    int r_num = 0;
#ifdef HAVOK_COMPILE
    ActorId32 actor = m_actor;
    hkaAnimatedSkeleton* s = m_skeleton;
    int num = s->getNumAnimationControls();
    for (int i=0; i<num; ++i)
    {
        hk_anim_ctrl* ac = (hk_anim_ctrl*)s->getAnimationControl(i);
        if(ac->getWeight() < ANIM_EVT_WEIGHT_THRESHOLD)
            continue;
        const Animation* anim = ac->m_animation;
        if (!anim)
            continue;
        AnimationTrigger* triggers = 0;
        float local_time = ac->getLocalTime();
        int frame = (int)(local_time * ANIMATION_FRAME_FPS);
        int t_num = get_animation_triggers(anim, frame, &triggers);
        for(int j=0; j<t_num; ++j)
        {
            events[j].m_name = triggers[j].m_name;
            events[j].m_who = actor;
        }
        events += t_num;
        r_num += t_num;
    }
#endif
    return r_num;
}


