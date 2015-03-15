#pragma once
#include "BaseTypes.h"
#include "StringId.h"
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>

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

#ifndef _RETAIL
typedef tinystl::unordered_map<void*, const char*> anim_debug_map;
#endif

struct AnimationSystem
{
    void    init(const AnimationConfig& cfg);
    void    shutdown();

    void    frame_start();
    void    kickin_jobs();
    void    tick_finished_jobs();
    void    update_attachment(Actor* actors, int num);
    void    skin_actors(Actor* actors, int num);
    void    update_animations(float dt);

    static void register_factories();

    int                     m_numAnimEvts;
    AnimationEvent*         m_events;
    float                   m_time;
    float                   m_time_scale;

#ifndef _RETAIL
    anim_debug_map  m_anim_debug_names;
    void add_anim_debug_name(void* p, StringId name)
    {
        anim_debug_map::iterator i = m_anim_debug_names.find(p);
        if(i != m_anim_debug_names.end())
            return;
        m_anim_debug_names[p] = stringid_lookup(name);
    }
#endif
};

extern AnimationSystem g_animMgr;

Id create_anim_rig( const void*, ActorId32);
void destroy_anim_rig( Id );
void* get_anim_rig( Id );
int num_all_anim_rig();
void* get_all_anim_rig();
void  lookup_anim_rig_instance_data( void* );

Id create_anim_state( const void*, ActorId32);
void destroy_anim_state( Id );
void* get_anim_state( Id );
int num_all_anim_state();
void* get_all_anim_state();
void  lookup_anim_state_instance_data(void*);
