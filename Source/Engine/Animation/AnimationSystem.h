#pragma once
#include "Prerequisites.h"

class hkaSkeleton;
class hkaAnimatedSkeleton;
class hkaPose;
class hkLoader;
class hkaMirroredSkeleton;
class hkaAnimation;
class hkaMirroredAnimation;
class hkaAnimationBinding;

struct AnimationSystem
{
    void    init();
    void    quit();

    void    frameStart();
    void    kickInJobs();
    void    tickFinishJobs();
    void    checkStatus();

private:
    int     m_status;
};

extern AnimationSystem g_animMgr;



