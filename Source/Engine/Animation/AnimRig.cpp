#include "AnimRig.h"
#include "Resource.h"
#include "Log.h"
#include "Animation.h"
#include "MemorySystem.h"
#include "MathDefs.h"
#include "Utils.h"
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
    uint8_t                 m_motionType;
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


static void ease_in_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    char* offset = cmds.m_params;
    float f_time = *(float*)(offset);
    uint8_t i_control = *(uint8_t*)(offset + sizeof(float));
    uint8_t i_type = *(uint8_t*)(offset + sizeof(float) + sizeof(uint8_t));
    hk_anim_ctrl* control = inst->get_control(i_control);
    if(!control->m_enabled) inst->m_skeleton->addAnimationControl(control);
    control->ease_in(f_time, i_type);
}
static void ease_out_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    char* offset = cmds.m_params;
    float f_time = *(float*)(offset);
    uint8_t i_control = *(uint8_t*)(offset + sizeof(float));
    uint8_t i_type = *(uint8_t*)(offset + sizeof(float) + sizeof(uint8_t));
    hk_anim_ctrl* control = inst->get_control(i_control);
    control->ease_out(f_time, i_type);
}
static void set_time_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    char* offset = cmds.m_params;
    float f_time = *(float*)(offset);
    uint8_t i_control = *(uint8_t*)(offset + sizeof(float));
    hk_anim_ctrl* control = inst->get_control(i_control);
    control->setLocalTime(f_time);
}
static void set_speed_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    char* offset = cmds.m_params;
    float f_speed = *(float*)(offset);
    uint8_t i_control = *(uint8_t*)(offset + sizeof(float));
    hk_anim_ctrl* control = inst->get_control(i_control);
    control->setPlaybackSpeed(f_speed);
}
static void set_weight_animation_command(const Command& cmd, void* context)
{
    AnimRigInstance* inst = (AnimRigInstance*)(context);
    char* offset = cmds.m_params;
    float f_weight = *(float*)(offset);
    uint8_t i_control = *(uint8_t*)(offset + sizeof(float));
    hk_anim_ctrl* control = inst->get_control(i_control);
    control->setMasterWeight(f_weight);
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
void  lookup_resource_anim_rig(void * resource)
{
    AnimRig* rig = (AnimRig*)resource;
    for (uint32_t i=0; i<rig->m_numAnimations; ++i)
    {
        rig->m_animations[i] = FIND_RESOURCE(Animation, rig->m_animNames[i]);
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

void AnimRigInstance::init( const void* resource )
{
    m_attachmentTransforms = 0;
    m_applyRootmotion = true;
    m_resource = (const AnimRig*)resource;
    const hkaSkeleton* skeleton = m_resource->m_skeleton;
    uint32_t ctrl_size = sizeof(hk_anim_ctrl);
    ctrl_size *= m_resource->m_numAnimations;
    uint32_t mem_size = sizeof(hkaSkeleton) + sizeof(hkaPose) + ctrl_size + CommandMachine::caculate_memory(32, kAnimCmdMax);
    m_blob = COMMON_ALLOC(char, mem_size);
    memset(m_blob, 0x00, mem_size);
    char* offset = m_blob;
    //uint32_t pose_mem_size = hkaPose::getRequiredMemorySize(m_resource->m_skeleton);
    m_skeleton = new(offset) hkaAnimatedSkeleton(skeleton);
    offset += sizeof(hkaAnimatedSkeleton);
    m_pose = new(offset) hkaPose(skeleton);
    m_pose->setToReferencePose();
    m_pose->syncAll();
    offset += sizeof(hkaPose);
    m_numControls = m_resource->m_numAnimations;
    for (uint32_t i=0; i<m_numControls; ++i)
    {
        m_controls[i] = new (offset) hk_anim_ctrl(m_resource->m_animations[i]);
        offset += sizeof(hk_anim_ctrl);
    }
    m_animMachine = (CommandMachine*)offset;
    m_animMachine->init(32, kAnimCmdMax);
    m_animMachine->m_context = this;
    m_animMachine->m_commandCallbacks[kAnimCmdEaseIn] = ease_in_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdEaseOut] = ease_out_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdSetWeight] = set_weight_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdSetSpeed] = set_speed_animation_command;
    m_animMachine->m_commandCallbacks[kAnimCmdSetTime] = set_time_animation_command;
}

void AnimRigInstance::destroy()
{
    for (uint32_t i=0; i<m_numControls; ++i)
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


void AnimRigInstance::update_attachments( const hkQsTransform& worldFromModel )
{
    uint32_t num = m_resource->m_attachNum;
    const BoneAttachment* attachments = m_resource->m_attachments;
    m_attachmentTransforms = FRAME_ALLOC(float, num*16);
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
    m_applyRootmotion = false;
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

void AnimRigInstance::easein_animation(int index, float blend_time, bool bloop, float when, int type)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kAnimCmdEaseIn;
    char* offset = cmd.m_params;
    *(float*)(offset) = blend_time;
    *(uint8_t*)(offset + sizeof(float)) = index;
    *(uint8_t*)(offset + sizeof(float) + sizeof(uint8_t)) = type;
    m_animMachine->addCommand(cmd);
}

void AnimRigInstance::easeout_animation(int index, float blend_time, float when, int type)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kAnimCmdEaseOut;
    char* offset = cmd.m_params;
    *(float*)(offset) = blend_time;
    *(uint8_t*)(offset + sizeof(float)) = index;
    *(uint8_t*)(offset + sizeof(float) + sizeof(uint8_t)) = type;
    m_animMachine->addCommand(cmd);
}


void AnimRigInstance::set_animation_weight( int index, float weight, float when )
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kAnimCmdSetWeight;
    char* offset = cmd.m_params;
    *(float*)(offset) = weight;
    *(uint8_t*)(offset + sizeof(float)) = index;
    m_animMachine->addCommand(cmd);
}

void AnimRigInstance::set_animation_speed( int index, float speed, float when )
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kAnimCmdSetSpeed;
    char* offset = cmd.m_params;
    *(float*)(offset) = weight;
    *(uint8_t*)(offset + sizeof(float)) = index;
    m_animMachine->addCommand(cmd);
}

void AnimRigInstance::set_animation_time( int index, float local_time, float when )
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kAnimCmdSetTime;
    char* offset = cmd.m_params;
    *(float*)(offset) = weight;
    *(uint8_t*)(offset + sizeof(float)) = index;
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

void AnimRigInstance::get_rootmotion(float dt, hkQsTransform& t ) const
{
    m_skeleton->getDeltaReferenceFrame(dt, t);
}

void AnimRigInstance::get_rootmotion( int index, float dt, hkQsTransform& t ) const
{
    m_controls[index]->getExtractedMotionDeltaReferenceFrame(dt, t);
}


