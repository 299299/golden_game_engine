#pragma once
#include "BaseTypes.h"

class hkaSkeleton;
class hkaAnimatedSkeleton;
class hkaPose;
class hkLoader;
class hkaMirroredSkeleton;
class hkaAnimation;
class hkaMirroredAnimation;
class hkaAnimationBinding;

struct AnimRig;
struct AnimRigInstance;
struct Actor;
struct AnimationEvent;
class hkaSampleBlendJob;

struct AnimationConfig
{
    int    max_rigs;
    int    max_state_layers;
    int    max_anim_events;
};

struct AnimationSystem
{
    void    init(const AnimationConfig& cfg);
    void    shutdown();

    void    frame_start();
    void    kick_in_jobs();
    void    tick_finished_jobs();
    void    update_attachment(Actor* actors, uint32_t num);
    void    skin_actors(Actor* actors, uint32_t num);
    void    update_animations(float dt);

    static void register_factories();

    uint32_t                m_numAnimEvts;
    AnimationEvent*         m_events;
    float                   m_time;
    float                   m_time_scale;
};

extern AnimationSystem g_animMgr;

Id create_anim_rig( const void*, ActorId32);
void destroy_anim_rig( Id );
void* get_anim_rig( Id );
uint32_t num_all_anim_rig();
void* get_all_anim_rig();
void  lookup_anim_rig_instance_data( void* );

Id create_anim_state( const void*, ActorId32);
void destroy_anim_state( Id );
void* get_anim_state( Id );
uint32_t num_all_anim_state();
void* get_all_anim_state();
void  lookup_anim_state_instance_data(void*);
