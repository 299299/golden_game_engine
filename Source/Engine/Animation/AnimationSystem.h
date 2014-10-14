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

struct AnimFSM;
struct AnimFSMInstance;
struct AnimRig;
struct AnimRigInstance;
struct Actor;
struct AnimationEvent;

struct AnimationSystem
{
    void    init();
    void    quit();

    void    frame_start();
    void    kick_in_jobs();
    void    tick_finished_jobs();
    void    skin_actors(Actor* actors, uint32_t num);
    void    update_local_clocks(float dt);
    void    update_fsms(float dt);

    AnimationEvent* alloc_event();

    uint32_t                m_numAnimEvts;
    AnimationEvent*         m_events;
};
extern AnimationSystem g_animMgr;



