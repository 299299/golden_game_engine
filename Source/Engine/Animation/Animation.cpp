#include "Animation.h"
#include "Log.h"
#include "Resource.h"
#include "AnimRig.h"
#include "DebugDraw.h"
#include "MathDefs.h"
#include "Utils.h"
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

const AnimationBeat* Animation::find_beat(uint32_t type) const
{
    for (uint32_t i = 0; i < m_numBeats; ++i)
    {
        if(m_beats[i].m_type == type)
            return &m_beats[i];
    }
    return 0;
}

const AnimationBeat* Animation::find_next_closest_beat(float time, bool bLoop) const
{
    if(!m_numBeats || time >= get_length())
        return 0;

    if(!bLoop)
    {
        for(uint32_t i = 0; i < m_numBeats; ++i)
        {
            const AnimationBeat& b = m_beats[i];
            if(b.m_time >= time)
                return &b;
        }
        return 0;
    }
    else
    {
        uint32_t i = 0;
        for(; i < m_numBeats; ++i)
        {
            const AnimationBeat& b = m_beats[i];
            if(b.m_time >= time)
                break;
        }
        if(i >= m_numBeats)
            i = 0;
        return m_beats;
    }
}

int Animation::get_frames() const
{
    return m_animation->getNumOriginalFrames();
}

float Animation::get_length() const
{
    return m_animation->m_duration;
}

uint8_t Animation::collect_triggers( float curTime, float dt, AnimationTrigger* outTriggers ) const
{
    uint8_t retNum = 0;
    uint8_t startIndex = INVALID_U8;
    for(uint8_t i=0; i<m_numTriggers; ++i)
    {
        const AnimationTrigger& trigger  = m_triggers[i];
        float tTime = trigger.m_time;
        if(tTime > curTime && tTime + dt < curTime)
        {
            ++retNum;
            if(startIndex == INVALID_U8)
                startIndex = i;
        }
    }

    if(startIndex == INVALID_U8)
        return 0;

    memcpy(outTriggers, &m_triggers[startIndex], retNum * sizeof(AnimationTrigger));
    return retNum;
}

void Animation::dump()
{
    LOGI("dump animation ------------------>");
    LOGI("mirrorered=%s, rig=%s, numTriggers=%d, numBeats=%d", 
         stringid_lookup(m_mirroredFrom), stringid_lookup(m_rigName),  m_numTriggers, m_numBeats);
    for(uint32_t i=0; i<m_numTriggers; ++i)
    {
        const AnimationTrigger& t = m_triggers[i];
        LOGI("trigger name=%s, time=%f", stringid_lookup(t.m_name), t.m_time);
    }

    extern const char* g_beatTypeNames[];
    for(uint32_t i=0; i<m_numBeats; ++i)
    {
        const AnimationBeat& b = m_beats[i];
        LOGI("beat type=%s, time=%f", g_beatTypeNames[b.m_type], b.m_time);
    }
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
#ifdef DUMP_RESOURCE
    anim->dump();
#endif
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
                                 pose.getSyncedPoseModelSpace().begin(), worldFromModel, color );


    if (showLabels)
    {
        hkDebugDisplay& d = hkDebugDisplay::getInstance();
        const hkInt16* parents = skeleton->m_parentIndices.begin();
        const hkQsTransform* bones = pose.getSyncedPoseModelSpace().begin();
        for (int i=0; i<skeleton->m_bones.getSize(); i++)
        {
            hkVector4 p1, p2;
            p1 = bones[i].getTranslation();
            if (parents[i] == -1)
            {
                p2 = p1;
            }
            else
            {
                p2 = bones[parents[i]].getTranslation();
            }

            hkVector4 bonemid;
            bonemid = p1; bonemid.setAdd4(bonemid, p2); bonemid.setMul4(0.5f, bonemid);
            bonemid.setTransformedPos(worldFromModel, bonemid);

            hkStringBuf s;
            s.printf("%d", i);
            d.display3dText(s.cString(), bonemid, color, 0, 0);
        }
    }
}

void draw_pose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color, hkBool showLabels)
{
    const hkaSkeleton* skeleton = pose.getSkeleton();
    const hkArray<hkInt16>& parentIndices = skeleton->m_parentIndices;
    const hkArray<hkQsTransform>& poseMS = pose.getSyncedPoseModelSpace();
    float start[3], end[3];
    for (int i=0; i < poseMS.getSize(); ++i)
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
    }
}

