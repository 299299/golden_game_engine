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

struct AnimationSystem
{
    void    init();
    void    quit();

    void    frameStart();
    void    kickInJobs();
    void    tickFinishJobs();
    void    checkStatus();

    Id      create_fsm(const AnimFSM* resource);
    void    destroy_fsm(Id id);
    AnimFSMInstance* get_fsm(Id id);

    Id      create_rig(const AnimRig* resource);
    void    destroy_rig(Id id);
    AnimRigInstance* get_rig(Id id);

private:
    int                                         m_status;
};

extern AnimationSystem g_animMgr;



