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

struct AnimationTrigger
{
    StringId                        m_name;
    float                           m_time;
};

ENGINE_NATIVE_ALIGN(struct) Animation
{
    int get_frames() const;
    float get_length() const;

    int  find_first_trigger(StringId name) const;
    int  find_next_closest_trigger(float time, bool bLoop) const;
    uint32_t collect_triggers(float curTime, float dt, AnimationEvent* events) const;
    const AnimationTrigger* get_triggers() const;

    StringId                        m_mirrored_from;
    StringId                        m_rig_name;

    hkaAnimation*                   m_animation;
    hkaAnimationBinding*            m_binding;

    uint32_t                        m_trigger_offset;
    uint32_t                        m_num_triggers;

    uint32_t                        m_havok_data_offset;
    uint32_t                        m_havok_data_size;
};


void* load_resource_animation( void*, uint32_t);
void destroy_resource_animation( void * );
void lookup_resource_animation( void * );
void create_mirrored_animation(const Animation* orginalAnim, Animation* newAnim);

//======================================================================
//          HELPER API
//======================================================================
float caculate_motion_velocity(hkaDefaultAnimationControl* ac);
void draw_pose_vdb( const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
void draw_pose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
