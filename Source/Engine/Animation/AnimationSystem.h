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

struct AnimationSystem
{
    void    init();
    void    quit();

    void    frameStart();
    void    kickInJobs();
    void    tickFinishJobs();
    void    skin_actors(Actor* actors, uint32_t num);
};
extern AnimationSystem g_animMgr;



