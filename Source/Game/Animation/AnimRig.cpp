#include "AnimRig.h"
#include "Resource.h"
#include "Log.h"
#include "Animation.h"
#include "MemorySystem.h"
#include "MathDefs.h"
#include "Utils.h"
#include "AnimControl.h"
#include <bx/fpumath.h>
//=======================================================================================
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Animation/Animation/Animation/ReferencePose/hkaReferencePoseAnimation.h>
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
//=======================================================================================

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
	//animations
	rig->m_animNames = (StringId*)offset;
	offset += sizeof(StringId) * rig->m_numAnimations;
	rig->m_animations = (Animation**)offset;
	offset += sizeof(StringId) * rig->m_numAnimations;
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
    uint32_t num = rig->m_numAnimations;
    Animation** head = rig->m_animations;
    StringId* nameHead = rig->m_animNames;
    for (uint32_t i=0; i<num; ++i)
    {
        head[i] = FIND_RESOURCE(Animation, nameHead[i]);
    }
}
void  destroy_resource_anim_rig(void * resource)
{
    AnimRig* rig = (AnimRig*)resource;
    char* p = (char*)resource + rig->m_havokDataOffset;
    SAFE_REMOVEREF(rig->m_mirroredSkeleton);
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
}

int AnimRig::find_animation_index( const StringId& name ) const
{
    int num = m_numAnimations;
    StringId* names = m_animNames;
    for (int i=0; i<num; ++i)
    {
        if(names[i] == name) return i;
    }
    return -1;
}

//------------------------------------------------------------------------------------------------
//          INSTANCE
//------------------------------------------------------------------------------------------------

void AnimRigInstance::init( const void* resource , ActorId32 actor)
{
    m_actor = actor;
    m_attachmentTransforms = 0;
    m_resource = (const AnimRig*)resource;
    const hkaSkeleton* skeleton = m_resource->m_skeleton;
    uint32_t numAnimations = m_resource->m_numAnimations;
    uint32_t ctrl_size = sizeof(hk_anim_ctrl);
    ctrl_size *= numAnimations;
	//uint32_t pose_mem_size = hkaPose::getRequiredMemorySize(skeleton);
	uint32_t pose_size = sizeof(hkaPose);
	pose_size = HK_NEXT_MULTIPLE_OF(16, pose_size);
    uint32_t mem_size = sizeof(hkaSkeleton) + pose_size + ctrl_size + sizeof(hk_anim_ctrl*) * numAnimations;
    m_blob = COMMON_ALLOC(char, mem_size);
    memset(m_blob, 0x00, mem_size);
    char* offset = m_blob;
    m_skeleton = new(offset) hkaAnimatedSkeleton(skeleton);
    offset += sizeof(hkaAnimatedSkeleton);
    m_pose = new(offset) hkaPose(skeleton);
    m_pose->setToReferencePose();
    m_pose->syncAll();
    if(numAnimations > 0) m_skeleton->setReferencePoseWeightThreshold(0.0f);
    offset += pose_size;
    m_numControls = numAnimations;
	char* ptr = offset;
	offset += sizeof(hk_anim_ctrl) * numAnimations;
    m_controls = (hk_anim_ctrl**)offset;
    offset += sizeof(hk_anim_ctrl*) * numAnimations;
	Animation** anims = m_resource->m_animations;
    for (uint32_t i=0; i<numAnimations; ++i)
    {
        m_controls[i] = new (ptr) hk_anim_ctrl(anims[i]);
        ptr += sizeof(hk_anim_ctrl);
    }
}

void AnimRigInstance::destroy()
{
    uint32_t num = m_numControls;
    for (uint32_t i=0; i<num; ++i)
    {
        SAFE_DESTRUCTOR(m_controls[i], hk_anim_ctrl);
    }
    SAFE_DESTRUCTOR(m_pose, hkaPose);
    SAFE_DESTRUCTOR(m_skeleton, hkaAnimatedSkeleton);
    COMMON_DEALLOC(m_blob);
}

void AnimRigInstance::update(float dt)
{
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
}

void AnimRigInstance::update_attachment( const hkQsTransform& worldFromModel )
{
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
}


bool AnimRigInstance::is_playing_animation() const
{   
    int num = m_skeleton->getNumAnimationControls();
    for(int i=0; i<num; ++i)
    {
        hk_anim_ctrl* ac = (hk_anim_ctrl*)m_skeleton->getAnimationControl(i);
        float speed = ac->getPlaybackSpeed();
        if(speed > 0.0f) return true;
    }
    return false;
}

bool AnimRigInstance::is_playing_animation(int index) const
{
    hk_anim_ctrl* ac = get_control(index);
    if(!ac->m_enabled) return false;
    if(ac->getPlaybackSpeed() > 0.0f) return true;
    return false;
}

void AnimRigInstance::test_animation(const char* name)
{
    Animation* anim = FIND_RESOURCE_NAMED(Animation, name);
    if(!anim) return;
    hk_anim_ctrl* ac = new hk_anim_ctrl(anim);
    ac->easeIn(0.0f);
    m_skeleton->addAnimationControl(ac);
    m_skeleton->setReferencePoseWeightThreshold(0.0f);
    ac->m_enabled = true;
    ac->set_loop(true);
    ac->removeReference();
}

hk_anim_ctrl* AnimRigInstance::get_control( int index ) const
{
    return m_controls[index];
}

int AnimRigInstance::find_control(const StringId& name) const
{
    uint32_t num = m_numControls;
    hk_anim_ctrl** head = m_controls;
    for (uint32_t i = 0; i < num; ++i)
    {
        hk_anim_ctrl* ac = head[i];
        if(ac->m_name == name) return i; 
    }
    return -1;
}

float AnimRigInstance::get_animation_weight( int index ) const
{
    return m_controls[index]->get_weight();
}

float AnimRigInstance::get_animation_speed( int index ) const
{
    return m_controls[index]->getPlaybackSpeed();
}

float AnimRigInstance::get_animation_time( int index ) const
{
    return m_controls[index]->getLocalTime();
}

float AnimRigInstance::get_animation_period( int index ) const
{
    return m_controls[index]->get_peroid();
}

void AnimRigInstance::get_rootmotion(float dt, hkQsTransform& t ) const
{
    m_skeleton->getDeltaReferenceFrame(dt, t);
}

void AnimRigInstance::get_rootmotion( int index, float dt, hkQsTransform& t ) const
{
    m_controls[index]->getExtractedMotionDeltaReferenceFrame(dt, t);
}

float AnimRigInstance::get_beat_time( int index, int beat_index ) const
{
    return m_controls[index]->m_animation->get_beat(beat_index).m_time;
}

int AnimRigInstance::get_beat_type( int index, int beat_index ) const
{
    return m_controls[index]->m_animation->get_beat(beat_index).m_type;
}

int AnimRigInstance::get_closest_beat( int index ) const
{
    hk_anim_ctrl* ac = m_controls[index];
    return ac->m_animation->find_next_closest_beat(ac->getLocalTime(), ac->is_loop());
}

int AnimRigInstance::get_first_beat( int index, int type ) const
{
    return m_controls[index]->m_animation->find_first_beat(type);
}

float AnimRigInstance::next_anim_sync_time( int indexA, int indexB ) const
{
    hk_anim_ctrl* acA = m_controls[indexA];
    hk_anim_ctrl* acB = m_controls[indexB];
    Animation* animA = acA->m_animation;
    Animation* animB = acB->m_animation;
    int beat_index = animA->find_next_closest_beat(acA->getLocalTime(), acA->is_loop());
    if(beat_index < 0) return -1;
    int beat_type = animA->get_beat(beat_index).m_type;
    beat_index = animB->find_first_beat(beat_type);
    if(beat_index < 0) return -1;
    return animB->get_beat(beat_index).m_time;
}

