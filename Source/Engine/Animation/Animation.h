#pragma once
#include "StringId.h"
#include "Prerequisites.h"

class hkLoader;
class hkaAnimation;
class hkaAnimationBinding;
class hkaDefaultAnimationControl;
class hkaPose;

#define ANIMATION_FRAME_FPS          (30.0f)
#define ANIMATION_TIME_PERFRAME      (1.0f/30.0f)

inline int timeToFrame(float fTime)
{
    return (int)(fTime * ANIMATION_FRAME_FPS);
}

inline float frameToTime(int frame)
{
    return frame * ANIMATION_TIME_PERFRAME;
}


enum AnimBeatType
{
    kAnimBeatLeftFootDown,
    kAnimBeatRightFootDown,
};

struct AnimationBeat
{
    float                           m_time;
    uint8_t                         m_type;
    char                            m_padding[3];
};

struct AnimationTrigger
{
    StringId                        m_name;
    float                           m_time;
};

ENGINE_NATIVE_ALIGN struct Animation
{
    DECLARE_RESOURCE(animation);

    void lookup();
    void destroy();

    int getFrames() const;
    float getLength() const;
    bool isMirrored() const { return !m_mirroredFrom.isZero();};
    
    const AnimationBeat* findBeat(uint32_t type) const;
    const AnimationBeat* findNextClosestBeat(float time, bool bLoop) const;
    uint8_t collectTriggers(float curTime, float dt, AnimationTrigger* outTriggers) const;

    void createMirrorAnimation(const Animation* orginalAnim);

    StringId                        m_mirroredFrom;
    StringId                        m_rigName;

    hkaAnimation*                   m_animation;
    hkaAnimationBinding*            m_binding;

    AnimationTrigger*               m_triggers;
    AnimationBeat*                  m_beats;

    uint32_t                        m_havokDataOffset;
    uint32_t                        m_havokDataSize;

    uint8_t                         m_numTriggers;
    uint8_t                         m_numBeats;
    char                            m_padding[2];

    void dump();
};


void* load_resource_animation(const char* data, uint32_t size);
void  destroy_resource_animation(void * resource);
void  lookup_resource_animation(void * resource);

//======================================================================
//          HELPER API
//======================================================================
hkReal caculateMotionVelocity(hkaDefaultAnimationControl* ac);
// Compute the blend params that will produce the desired velocity
void computeBlendParams(hkReal desiredVel, hkReal walkVel, hkReal runVel, 
                        hkReal walkDur, hkReal runDur, hkReal& blend, 
                        hkReal& walkSpeed, hkReal& runSpeed );
void drawPoseVDB( const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
void drawPose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
