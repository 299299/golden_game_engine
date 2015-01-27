#include "AnimRig.h"
#include "Resource.h"
#include "Log.h"
#include "Animation.h"
#include "MemorySystem.h"
#include "MathDefs.h"
#include "Utils.h"
#include "AnimControl.h"
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

//------------------------------------------------------------------------------------------------
//          RESOURCE
//------------------------------------------------------------------------------------------------

void* load_resource_anim_rig(const char* data, uint32_t size)
{
    AnimRig* rig = (AnimRig*)data;
    const char* offset = data;
    offset += sizeof(AnimRig);
    //joint names
    rig->m_jointNames = (StringId*)(offset);
    offset += sizeof(StringId) * rig->m_jointNum;
    //bone attachments
    rig->m_attachments = (BoneAttachment*)offset;
    offset = data + rig->m_havokDataOffset;
    rig->m_skeleton = (hkaSkeleton*)load_havok_inplace((void*)offset, rig->m_havokDataSize);
    if(rig->m_mirrored) rig->create_mirrored_skeleton();
    return rig;
}
void  lookup_resource_anim_rig(void * resource)
{
    AnimRig* rig = (AnimRig*)resource;
    // FIXME:TODO
}
void  destroy_resource_anim_rig(void * resource)
{
    AnimRig* rig = (AnimRig*)resource;
    char* p = (char*)resource + rig->m_havokDataOffset;
#ifdef HAVOK_COMPILE
    SAFE_REMOVEREF(rig->m_mirroredSkeleton);
#endif
    unload_havok_inplace(p, rig->m_havokDataSize);
}

int AnimRig::find_joint_index(const StringId& jointName) const
{
    int num = m_jointNum;
    StringId* head = m_jointNames;
    for(int i=0; i<num; ++i)
    {
        if(head[i] == jointName)
            return i;
    }
    return -1;
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
    m_mirroredSkeleton = new hkaMirroredSkeleton( m_skeleton );
    m_mirroredSkeleton->computeBonePairingFromNames( ltag, rtag );
    hkQuaternion v_mir( -1.0f, 0.0f, 0.0f, 0.0f );
    m_mirroredSkeleton->setAllBoneInvariantsFromReferencePose( v_mir, 0.0f );
#endif
}

//------------------------------------------------------------------------------------------------
//          INSTANCE
//------------------------------------------------------------------------------------------------

void AnimRigInstance::init( const void* resource , ActorId32 actor)
{
    m_actor = actor;
    m_attachmentTransforms = 0;
    m_resource = (const AnimRig*)resource;
#ifdef HAVOK_COMPILE
    const hkaSkeleton* skeleton = m_resource->m_skeleton;
    //uint32_t pose_mem_size = hkaPose::getRequiredMemorySize(skeleton);
    uint32_t pose_size = sizeof(hkaPose);
    pose_size = NEXT_MULTIPLE_OF(16, pose_size);
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
}

void AnimRigInstance::update_attachment( const hkQsTransform& worldFromModel )
{
#ifdef HAVOK_COMPILE
    uint32_t num = m_resource->m_attachNum;
    m_attachmentTransforms = FRAME_ALLOC(float, num*16);
    const BoneAttachment* attachments = m_resource->m_attachments;
    const hkArray<hkQsTransform>& poseInWorld = m_pose->getSyncedPoseModelSpace();
    for (uint32_t i=0; i<num; ++i)
    {
        const BoneAttachment& ba = attachments[i];
        hkQsTransform boneWS;
        boneWS.setMul(worldFromModel, poseInWorld[ba.m_boneIndex]);
        hkMatrix4 worldFromBone; worldFromBone.set(boneWS);
        hkMatrix4 boneFromAttachment; transform_matrix(boneFromAttachment, ba.m_boneFromAttachment);
        hkMatrix4 worldFromAttachment; worldFromAttachment.setMul(worldFromBone, boneFromAttachment);
        transform_matrix(m_attachmentTransforms + i*16, worldFromAttachment);
    }
#endif
}

void AnimRigInstance::test_animation(const char* name)
{
#ifdef HAVOK_COMPILE
    Animation* anim = FIND_RESOURCE_NAMED(Animation, name);
    if(!anim) return;
    hk_anim_ctrl* ac = new hk_anim_ctrl(anim);
    ac->easeIn(0.0f);
    m_skeleton->addAnimationControl(ac);
    m_skeleton->setReferencePoseWeightThreshold(0.0f);
    ac->m_enabled = true;
    ac->set_loop(true);
    ac->removeReference();
#endif
}

