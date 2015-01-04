#pragma once
#include "StringId.h"
#include "Prerequisites.h"

class hkLoader;
class hkaAnimation;
class hkaAnimationBinding;
class hkaDefaultAnimationControl;
class hkaPose;
struct AnimationEvent;

#define ANIMATION_FRAME_FPS          (30.0f)
#define ANIMATION_TIME_PERFRAME      (1.0f/30.0f)

inline int tim_to_frame(float fTime)
{
    return (int)(fTime * ANIMATION_FRAME_FPS);
}

inline float frame_to_time(int frame)
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

    int get_frames() const;
    float get_length() const;
    bool mirrored() const { return m_mirroredFrom;};
    
    int  find_first_beat(uint32_t type) const;
    int  find_next_closest_beat(float time, bool bLoop) const;
    const AnimationBeat& get_beat(int index) const { return m_beats[index]; };

    uint32_t collect_triggers(float curTime, float dt, AnimationEvent* events) const;
    void create_mirrored_animation(const Animation* orginalAnim);

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
};

//======================================================================
//          HELPER API
//======================================================================
hkReal caculate_motion_velocity(hkaDefaultAnimationControl* ac);
void draw_pose_vdb( const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
void draw_pose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
