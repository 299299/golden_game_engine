#include "Animation.h"
#include "Log.h"
#include "Resource.h"
#include "AnimRig.h"
#include "DebugDraw.h"
#include "MathDefs.h"
#include "Utils.h"
#include "Profiler.h"
#include "Event.h"
//==========================================================================================
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
//==========================================================================================

void Animation::destroy()
{
    if(!m_mirroredFrom) return;
    if(m_binding) hkaMirroredAnimation::destroyMirroredBinding(m_binding);
    SAFE_REMOVEREF(m_animation);
}

void Animation::lookup()
{
    if(!m_mirroredFrom) return;
    create_mirrored_animation(FIND_RESOURCE(Animation, m_mirroredFrom));
}

void Animation::create_mirrored_animation(const Animation* orginalAnim)
{
    destroy();
    AnimRig* rig = FIND_RESOURCE(AnimRig, m_rigName);
    orginalAnim->m_animation->addReference();
    hkaMirroredAnimation* anim = new hkaMirroredAnimation(orginalAnim->m_animation, orginalAnim->m_binding, rig->m_mirroredSkeleton);
    m_binding = anim->createMirroredBinding();
    m_animation = anim;
}

float Animation::find_beat(uint32_t type) const
{
    uint32_t num = m_numBeats;
    AnimationBeat* head = m_beats;
    for (uint32_t i = 0; i < num; ++i)
    {
        if(head[i].m_type == type)
            return head[i].m_time;
    }
    return -1;
}

float Animation::find_next_closest_beat(float time, bool bLoop) const
{
    uint32_t num = m_numBeats;
    AnimationBeat* head = m_beats;

    if(!num || time >= get_length()) return -1;

    float retTime = -1;
    for(uint32_t i = 0; i < num; ++i)
    {
        float curTime = head[i].m_time;
        if(curTime >= time)
        {
            retTime = curTime;
            break;
        }
    }
    
    if(!bLoop) return -1;
    if(retTime < 0) retTime = m_beats[0].m_time;
    return retTime;
}

int Animation::get_frames() const
{
    return m_animation->getNumOriginalFrames();
}

float Animation::get_length() const
{
    return m_animation->m_duration;
}

uint32_t Animation::collect_triggers( float curTime, float dt, AnimationEvent* events ) const
{
    uint32_t num = m_numTriggers;
    AnimationTrigger* head = m_triggers;
    uint32_t retNum = 0;
    uint32_t startIndex = -1;
    for(uint32_t i=0; i<num; ++i)
    {
        const AnimationTrigger& trigger  = head[i];
        float tTime = trigger.m_time;
        if(tTime > curTime && tTime + dt < curTime)
        {
            events[retNum++].m_name = trigger.m_name;
        }
    }
    return retNum;
}

void* load_resource_animation( const char* data, uint32_t size)
{
    Animation* anim = (Animation*)data;
    anim->m_triggers = (AnimationTrigger*)(data + sizeof(Animation));
    anim->m_beats = (AnimationBeat*)(data + sizeof(Animation) + sizeof(AnimationTrigger) * anim->m_numTriggers);
    char* p = (char*)data + anim->m_havokDataOffset;
    hkaAnimationContainer* ac = (hkaAnimationContainer*)load_havok_inplace(p, anim->m_havokDataSize);
    anim->m_animation = ac->m_animations[0];
    anim->m_binding = ac->m_bindings[0];
    return anim;
}

void destroy_resource_animation( void * resource )
{
    Animation* anim = (Animation*)resource;
    anim->destroy();
}

void lookup_resource_animation( void * resource )
{
    Animation* anim = (Animation*)resource;
    anim->lookup();
}

//======================================================================
//          HELPER API
//======================================================================
hkReal caculate_motion_velocity(hkaDefaultAnimationControl* ac)
{
    hkaAnimation* animation = ac->getAnimationBinding()->m_animation;
    hkQsTransform animMotion;
    animation->getExtractedMotionReferenceFrame(animation->m_duration, animMotion );
    return hkReal(animMotion.m_translation.length3()) / animation->m_duration;
}


void draw_pose_vdb(const hkaPose& pose, const hkQsTransform& worldFromModel, int color, hkBool showLabels)
{
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
}

void draw_pose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color, hkBool showLabels)
{
    PROFILE(Animation_DrawPose);
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
}

