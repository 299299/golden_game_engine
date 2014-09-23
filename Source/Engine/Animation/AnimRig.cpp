#include "AnimRig.h"
#include "Resource.h"
#include "Log.h"
#include "Animation.h"
#include "Utils.h"
//=======================================================================================
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
//=======================================================================================


int AnimRig::find_joint_index(const StringId& jointName)
{
    for(int i=0; i<m_jointNum; ++i)
    {
        if(m_jointNames[i] == jointName)
            return i;
    }
    return -1;
}

void AnimRig::ceate_mirrored_skeleton()
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
    // Mirror this character about the X axis
    hkQuaternion v_mir( -1.0f, 0.0f, 0.0f, 0.0f );
    m_mirroredSkeleton->setAllBoneInvariantsFromReferencePose( v_mir, 0.0f );
}

void AnimRigInstance::destroy()
{
    SAFE_DELETE(m_pose);
    SAFE_REMOVEREF(m_skeleton);
}

int AnimRigInstance::get_triggers(int layer, float dt, AnimationTrigger* outTriggers)
{
    return 0;
}

void AnimRigInstance::udpate_localcock(float dt)
{
    m_skeleton->stepDeltaTime(dt);
}

void AnimRigInstance::init( const void* resource )
{
    m_resource = (const AnimRig*)resource;
    m_skeleton = new hkaAnimatedSkeleton(m_resource->m_skeleton);
    m_pose = new hkaPose(m_skeleton->getSkeleton());
    m_pose->setToReferencePose();
    m_pose->syncModelSpace();
}

void AnimRigInstance::test_animation( const char* animFile )
{
    Animation* anim = FIND_RESOURCE(Animation, StringId(animFile));
    hkaDefaultAnimationControl* ac = new hkaDefaultAnimationControl(anim->m_binding);
    m_skeleton->addAnimationControl(ac);
}

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
    if(rig->m_mirrored) rig->createMirrorSkeleton();
    return rig;
}

void  destroy_resource_anim_rig(void * resource)
{
    AnimRig* rig = (AnimRig*)resource;
    char* p = (char*)resource + rig->m_havokDataOffset;
    SAFE_REMOVEREF(rig->m_mirroredSkeleton);
    unload_havok_inplace(p, rig->m_havokDataSize);
}
