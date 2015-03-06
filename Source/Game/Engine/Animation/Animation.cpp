#include "Animation.h"
#include "Log.h"
#include "Resource.h"
#include "AnimRig.h"
#include "DebugDraw.h"
#include "MathDefs.h"
#include "Utils.h"
#include "Profiler.h"
#include "DataDef.h"

#ifdef HAVOK_COMPILE
#include <Animation/Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredAnimation.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Animation/Animation/Animation/hkaAnimationBinding.h>
#include <Animation/Animation/Animation/hkaAnnotationTrack.h>
#include <Animation/Animation/Animation/Interleaved/hkaInterleavedUncompressedAnimation.h>
#include <Animation/Animation/Motion/hkaAnimatedReferenceFrame.h>
#include <Animation/Animation/Motion/Default/hkaDefaultAnimatedReferenceFrame.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Animation/Animation/Animation/hkaAnnotationTrack.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#endif

void create_mirrored_animation(const Animation* orginalAnim, Animation* newAnim)
{
#ifdef HAVOK_COMPILE
    destroy_resource_animation(newAnim);
    AnimRig* rig = FIND_RESOURCE(AnimRig, EngineTypes::ANIMATION_RIG, newAnim->m_rig_name);
    orginalAnim->m_animation->addReference();
    hkaMirroredAnimation* anim = new hkaMirroredAnimation(
        orginalAnim->m_animation,
        orginalAnim->m_binding,
        rig->m_mirrored_skeleton);
    newAnim->m_binding = anim->createMirroredBinding();
    newAnim->m_animation = anim;
#endif
}

int Animation::find_first_trigger( StringId name ) const
{
    uint32_t num = m_num_triggers;
    const AnimationTrigger* head = get_triggers();
    for(uint32_t i=0; i<num; ++i)
    {
        if(head[i].m_name == name)
            return i;
    }
    return -1;
}

int Animation::find_next_closest_trigger(float time, bool bLoop) const
{
    int num = m_num_triggers;
    const AnimationTrigger* head = get_triggers();
    if(!num || time >= get_length()) return -1;
    for(int i = 0; i < num; ++i)
    {
        if(head[i].m_time >= time)
            return i;
    }
    return bLoop ? 0 : -1;
}

int Animation::get_frames() const
{
#ifdef HAVOK_COMPILE
    return m_animation->getNumOriginalFrames();
#else
    return 0;
#endif
}

float Animation::get_length() const
{
#ifdef HAVOK_COMPILE
    return m_animation->m_duration;
#else
    return 2.0f;
#endif
}

const AnimationTrigger* Animation::get_triggers() const
{
    char* p = (char*)this;
    const AnimationTrigger* t = (const AnimationTrigger*)(p + m_trigger_offset);
    return t;
}


void* load_resource_animation( void* data, uint32_t size)
{
    Animation* anim = (Animation*)data;
    char* p = (char*)data + anim->m_havok_data_offset;
#ifdef HAVOK_COMPILE
    hkaAnimationContainer* ac = (hkaAnimationContainer*)load_havok_inplace(p, anim->m_havok_data_size);
    anim->m_animation = ac->m_animations[0];
    anim->m_binding = ac->m_bindings[0];
#endif
    return anim;
}

void destroy_resource_animation( void * resource )
{
#ifdef HAVOK_COMPILE
    Animation* anim = (Animation*)resource;
    if(!anim->m_mirrored_from)
        return;
    if(anim->m_binding)
        hkaMirroredAnimation::destroyMirroredBinding(anim->m_binding);
    SAFE_REMOVEREF(anim->m_animation);
#endif
}

void lookup_resource_animation( void * resource )
{
    Animation* anim = (Animation*)resource;
    if(anim->m_mirrored_from != 0)
        create_mirrored_animation(
            FIND_RESOURCE(Animation, EngineTypes::ANIMATION, anim->m_mirrored_from), anim);
}

//======================================================================
//          HELPER API
//======================================================================
float caculate_motion_velocity(hkaDefaultAnimationControl* ac)
{
#ifdef HAVOK_COMPILE
    hkaAnimation* animation = ac->getAnimationBinding()->m_animation;
    hkQsTransform animMotion;
    animation->getExtractedMotionReferenceFrame(animation->m_duration, animMotion );
    return float(animMotion.m_translation.length3()) / animation->m_duration;
#else
    return 0.0f;
#endif
}


void draw_pose_vdb(const hkaPose& pose, const hkQsTransform& worldFromModel, int color, hkBool showLabels)
{
#ifdef HAVOK_COMPILE
    const hkaSkeleton* skeleton = pose.getSkeleton();

    HK_DISPLAY_MODEL_SPACE_POSE( skeleton->m_bones.getSize(),
                                 skeleton->m_parentIndices.begin(),
                                 pose.getSyncedPoseModelSpace().begin(),
                                 worldFromModel,
                                 color );

    if (!showLabels) return;

    hkDebugDisplay& d = hkDebugDisplay::getInstance();
    const hkInt16* parents = skeleton->m_parentIndices.begin();
    const hkQsTransform* bones = pose.getSyncedPoseModelSpace().begin();
    int num = skeleton->m_bones.getSize();

    for (int i=0; i<num; i++)
    {
        hkVector4 p1, p2;
        p1 = bones[i].getTranslation();
        if (parents[i] == -1) p2 = p1;
        else p2 = bones[parents[i]].getTranslation();

        hkVector4 bonemid;
        bonemid = p1; bonemid.setAdd4(bonemid, p2); bonemid.setMul4(0.5f, bonemid);
        bonemid.setTransformedPos(worldFromModel, bonemid);

        hkStringBuf s;
        s.printf("%d", i);
        d.display3dText(s.cString(), bonemid, color, 0, 0);
    }
#endif
}

void draw_pose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color, hkBool showLabels)
{
#ifdef HAVOK_COMPILE
    const hkaSkeleton* skeleton = pose.getSkeleton();
    const hkInt16* parentIndices = skeleton->m_parentIndices.begin();
    const hkQsTransform* poseMS = pose.getSyncedPoseModelSpace().begin();
    int num = pose.getSyncedPoseModelSpace().getSize();

    float start[3], end[3];
    for (int i=0; i < num; ++i)
    {
        hkInt16 parentIndex = parentIndices[i];
        if(parentIndex == -1)
        {
            hkVector4 poseT;
            poseT.setTransformedPos(worldFromModel,  poseMS[i].m_translation);
            transform_vec3(start, poseT);
            transform_vec3(end, worldFromModel.m_translation);
        }
        else
        {
            hkVector4 poseT;
            poseT.setTransformedPos(worldFromModel, poseMS[i].m_translation);
            transform_vec3(start, poseT);
            poseT.setTransformedPos(worldFromModel, poseMS[parentIndex].m_translation);
            transform_vec3(end, poseT);
        }
        g_debugDrawMgr.add_line(start, end, color, false);

        if(showLabels)
        {
            g_debugDrawMgr.add_text_3d(start, skeleton->m_bones[i].m_name.cString(), RGBCOLOR(70,125,200));
        }
    }
#endif
}

