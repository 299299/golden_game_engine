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
    uint32_t num_fsms();
    AnimFSMInstance* get_fsms();

    Id      create_rig(const AnimRig* resource);
    void    destroy_rig(Id id);
    AnimRigInstance* get_rig(Id id);
    uint32_t num_rigs();
    AnimRigInstance* get_rigs();

private:
    int                                         m_status;
};

extern AnimationSystem g_animMgr;



