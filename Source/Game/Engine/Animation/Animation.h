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

struct AnimationTrigger
{
    StringId    m_name;
};

ENGINE_NATIVE_ALIGN(struct) Animation
{
    int get_frames() const;
    float get_length() const;

    StringId                        m_mirrored_from;
    StringId                        m_rig_name;

    hkaAnimation*                   m_animation;
    hkaAnimationBinding*            m_binding;

    uint32_t                        m_num_frames;
    uint32_t                        m_num_triggers;
    uint32_t                        m_trigger_offset;
    uint32_t                        m_trigger_num_offset;

    uint32_t                        m_havok_data_offset;
    uint32_t                        m_havok_data_size;
};


void* load_resource_animation( void*, uint32_t);
void destroy_resource_animation( void * );
void lookup_resource_animation( void * );
void create_mirrored_animation(const Animation* orginalAnim, Animation* newAnim);

float get_animation_length(const Animation* anim);
int get_animation_triggers(const Animation* anim, int frame, AnimationTrigger** triggers);

//======================================================================
//          HELPER API
//======================================================================
float caculate_motion_velocity(hkaDefaultAnimationControl* ac);
void draw_pose_vdb( const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
void draw_pose(  const hkaPose& pose, const hkQsTransform& worldFromModel, int color=0x7fffffff, hkBool showLabels = false );
