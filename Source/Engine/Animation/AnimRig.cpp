#include "AnimRig.h"
#include "Resource.h"
#include "Log.h"
#include "Animation.h"
#include "MemorySystem.h"
#include "MathDefs.h"
#include "Uitls.h"
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


enum AnimationCommand
{
	kAnimCmdEaseIn = 0,
	kAnimCmdEaseOut,
	kAnimCmdSetWeight,
	kAnimCmdSetSpeed,
	kAnimCmdSetTime,
	kAnimCmdMax
};

struct hk_anim_ctrl : public hkaDefaultAnimationControl
{
    Animation*              m_animation;
    StringId                m_name;
    uint8_t					m_motionType;
    uint8_t                 m_layer;
    bool                    m_enabled;

    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_CONTROL);
    hk_anim_ctrl(Animation* anim)
    :hkaDefaultAnimationControl(anim->m_binding, false)
    ,m_animation(anim)
    ,m_enabled(false)
    ,m_motionType(kMotionDefault)
    ,m_layer(0)
    {

    }
    
    virtual void getExtractedMotionDeltaReferenceFrame( hkReal deltaTime, hkQsTransform& deltaMotionOut ) const HK_OVERRIDE
    {
        switch(m_motionType)
        {
        case kMotionDefault:
            __super::getExtractedMotionDeltaReferenceFrame(deltaTime, deltaMotionOut);
            break;
        case kMotionIgnoreRotation:
            __super::getExtractedMotionDeltaReferenceFrame(deltaTime, deltaMotionOut);
            deltaMotionOut.m_rotation.setIdentity();
            break;
        case kMotionIgnoreTranslation:
            __super::getExtractedMotionDeltaReferenceFrame(deltaTime, deltaMotionOut);
            deltaMotionOut.m_translation.setZero4();
            break;
        case kMotionIgnoreAll:
            return;
        default:
            return;
        }
    }

    void ease_in(float time, int type)
    {
		setOverflowCount(0);
		setUnderflowCount(0);
		setLocalTime(0.0f);
        switch(type)
        {
        case kEaseCurveLinear:setEaseInCurve(0, 0.33f, 0.66f, 1);break;
        case kEaseCurveFast:setEaseInCurve(0, 0, 0, 1);break;
        case kEaseCurveSmooth:
        default:setEaseInCurve(0, 0, 1, 1);break;
        }
        easeIn(time);
    }

    void ease_out(float time, int type)
    {
        switch(type)
        {
        case kEaseCurveLinear:setEaseInCurve(1, 0.66f, 0.33f, 0);break;
        case kEaseCurveFast:setEaseInCurve(1, 1, 0, 0);break;
        case kEaseCurveSmooth:
        default:setEaseInCurve(1, 1, 0, 0);break;
        }
        easeOut(time);
    }

    void set_weight(float fWeight){ setMasterWeight(fWeight); }
	float get_weight() const { return getMasterWeight(); };
    float get_peroid() const {return m_binding->m_animation->m_duration; }
	void set_loop(bool bLooped) { m_maxCycles = bLooped ? -1 : 1; }
	bool is_loop() const { return m_maxCycles < 0;} 
};

struct hk_anim_ctrl_params
{
    int         m_control;
    float       m_float;
    int         m_int;
};
static void ease_in_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
    hk_anim_ctrl* control = inst->get_control(params->m_control);
    if(!control->m_enabled) inst->m_skeleton->addAnimationControl(control);
    control->ease_in(params->m_float, params->m_int);
}
static void ease_out_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
    hk_anim_ctrl* control = inst->get_control(params->m_control);
    control->ease_out(params->m_float, params->m_int);
}
static void set_time_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
    hk_anim_ctrl* control = inst->get_control(params->m_control);
    control->setLocalTime(params->m_float);
}
static void set_speed_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
    hk_anim_ctrl* control = inst->get_control(params->m_control);
    control->setPlaybackSpeed(params->m_float);
}
static void set_weight_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
    hk_anim_ctrl* control = inst->get_control(params->m_control);
    control->setMasterWeight(params->m_float);
}

//------------------------------------------------------------------------------------------------
//          RESOURCE
//------------------------------------------------------------------------------------------------

void* load_resource_anim_rig(const char* data, uint32_t size)
{
    AnimRig* rig = (AnimRig*)data;
    const char* offset = data;
    offset += sizeof(AnimRig);
    rig->m_jointNames = (StringId*)(offset);
    offset += sizeof(StringId) * rig->m_jointNum;
    rig->m_attachments = (BoneAttachment*)offset;
    offset = data + rig->m_havokDataOffset;
    rig->m_skeleton = (hkaSkeleton*)load_havok_inplace((void*)offset, rig->m_havokDataSize);
    if(rig->m_mirrored) rig->create_mirrored_skeleton();
    return rig;
}

void  destroy_resource_anim_rig(void * resource)
{
    AnimRig* rig = (AnimRig*)resource;
    char* p = (char*)resource + rig->m_havokDataOffset;
    SAFE_REMOVEREF(rig->m_mirroredSkeleton);
    unload_havok_inplace(p, rig->m_havokDataSize);
}

int AnimRig::find_joint_index(const StringId& jointName)
{
    for(int i=0; i<m_jointNum; ++i)
    {
        if(m_jointNames[i] == jointName)
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

//------------------------------------------------------------------------------------------------
//          INSTANCE
//------------------------------------------------------------------------------------------------

void AnimRigInstance::init( const void* resource )
{
    m_attachmentTransforms = 0;
    m_resource = (const AnimRig*)resource;
    m_skeleton = new hkaAnimatedSkeleton(m_resource->m_skeleton);
    m_pose = new hkaPose(m_skeleton->getSkeleton());
    m_pose->setToReferencePose();
    m_pose->syncAll();
    //m_animMachine = CommandMachine::create_command_machine(32);
    m_animMachine->m_context = this;
    m_animMachine->m_commandCallbacks[kAnimCmdEaseIn] = ease_in_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdEaseOut] = ease_out_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdSetWeight] = set_weight_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdSetSpeed] = set_speed_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdSetTime] = set_time_animation_command;
}

void AnimRigInstance::destroy()
{
    SAFE_DELETE(m_pose);
    SAFE_REMOVEREF(m_skeleton);
}

void AnimRigInstance::update(float dt)
{
    m_skeleton->stepDeltaTime(dt);
    m_animMachine->update(dt);
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


void AnimRigInstance::update_attachments( const float* worldFromModel )
{
	uint32_t num = m_resource->m_attachNum;
	const BoneAttachment* attachments = m_resource->m_attachments;
	m_attachmentTransforms = FRAME_ALLOC(float, num*16);
	const hkArray<hkQsTransform>& poseInWorld = m_pose->getSyncedPoseModelSpace();
	hkMatrix4 worldPose; transform_matrix(worldPose, worldFromModel);
	for (uint32_t i=0; i<num; ++i)
	{
		const BoneAttachment& ba = attachments[i];
		hkMatrix4 worldFromBone; worldFromBone.set( poseInWorld [ ba.m_boneIndex ] );
		hkMatrix4 boneFromAttachment; transform_matrix(boneFromAttachment, ba.m_boneFromAttachment);
		hkMatrix4 worldFromAttachment; worldFromAttachment.setMul(worldFromBone, boneFromAttachment);
		hkMatrix4 finalAttachment; finalAttachment.setMul(worldFromAttachment, worldPose);
		transform_matrix(m_attachmentTransforms+i*16, finalAttachment);
	}
}


bool AnimRigInstance::is_playing_animation() const
{   
    int numControls = m_skeleton->getNumAnimationControls();
    for(int i=0; i<numControls; ++i)
    {
        hk_anim_ctrl* ac = (hk_anim_ctrl*)m_skeleton->getAnimationControl(i);
        float speed = ac->getPlaybackSpeed();
        if(speed > 0.0f) return true;
    }
    return false;
}

void AnimRigInstance::test_animation(const char* name)
{
    Animation* anim = FIND_RESOURCE(Animation, StringId(name));
    if(!anim) return;
    hk_anim_ctrl* ac = new hk_anim_ctrl(anim);
    ac->easeIn(0.0f);
    m_skeleton->addAnimationControl(ac);
    m_skeleton->setReferencePoseWeightThreshold(0.0f);
	ac->set_loop(true);
	ac->removeReference();
}

hk_anim_ctrl* AnimRigInstance::get_control( int index ) const
{
	return m_controls[index];
}

int AnimRigInstance::find_control(const StringId& name) const
{
	for (uint32_t i = 0; i < m_numControls; ++i)
	{
		hk_anim_ctrl* ac = m_controls[i];
		if(ac->m_name == name) return i; 
	}
	return -1;
}

void AnimRigInstance::easeout_layers( int layer, float time, int type)
{
	for (int i=0; i<m_skeleton->getNumAnimationControls(); ++i)
	{
		hk_anim_ctrl* ac = (hk_anim_ctrl*)m_skeleton->getAnimationControl(i);
		int ctrl_layer = (int)ac->m_layer;
		if(ctrl_layer != layer) continue;
		ac->ease_out(time, type);
	}
}

void AnimRigInstance::easein_animation(int index, float blend_time, float when, int type)
{
	Command cmd;
	cmd.m_time = when;
	cmd.m_command = kAnimCmdEaseIn;
	hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
	params->m_float = blend_time;
	params->m_int = type;
	params->m_control = index;
	m_animMachine->addCommand(cmd);
}

void AnimRigInstance::easeout_animation(int index, float blend_time, float when, int type)
{
	Command cmd;
	cmd.m_time = when;
	cmd.m_command = kAnimCmdEaseOut;
	hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
	params->m_float = blend_time;
	params->m_int = type;
	params->m_control = index;
	m_animMachine->addCommand(cmd);
}


void AnimRigInstance::set_animation_weight( int index, float weight, float when )
{
	Command cmd;
	cmd.m_time = when;
	cmd.m_command = kAnimCmdSetWeight;
	hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
	params->m_float = weight;
	params->m_control = index;
	m_animMachine->addCommand(cmd);
}

void AnimRigInstance::set_animation_speed( int index, float speed, float when )
{
	Command cmd;
	cmd.m_time = when;
	cmd.m_command = kAnimCmdSetSpeed;
	hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
	params->m_float = speed;
	params->m_control = index;
	m_animMachine->addCommand(cmd);
}

void AnimRigInstance::set_animation_time( int index, float local_time, float when )
{
	Command cmd;
	cmd.m_time = when;
	cmd.m_command = kAnimCmdSetTime;
	hk_anim_ctrl_params* params = (hk_anim_ctrl_params*)cmd.m_params;
	params->m_float = local_time;
	params->m_control = index;
	m_animMachine->addCommand(cmd);
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


