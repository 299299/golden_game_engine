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

struct AnimationTrigger
{
    StringId                        m_name;
    float                           m_time;
};

ENGINE_NATIVE_ALIGN(struct) Animation
{
    DECLARE_RESOURCE(animation);

    void lookup();
    void destroy();

    int get_frames() const;
    float get_length() const;
    bool mirrored() const { return m_mirroredFrom;};

    int  find_first_trigger(StringId name) const;
    int  find_next_closest_trigger(float time, bool bLoop) const;
    uint32_t collect_triggers(float curTime, float dt, AnimationEvent* events) const;
    void create_mirrored_animation(const Animation* orginalAnim);

    StringId                        m_mirroredFrom;
    StringId                        m_rigName;

    hkaAnimation*                   m_animation;
    hkaAnimationBinding*            m_binding;

    AnimationTrigger*               m_triggers;

    uint32_t                        m_havokDataOffset;
    uint32_t                        m_havokDataSize;

    uint32_t                        m_numTriggers;
};

//======================================================================
//          HELPER API
//======================================================================
hkReal caculate_motion_velocity(hkaDefaultAnimationControl* ac);
void draw_pose_vdb( const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
void draw_pose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
