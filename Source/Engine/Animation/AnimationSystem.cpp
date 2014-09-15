#include "AnimationSystem.h"
#include "Thread.h"
#include "MemorySystem.h"
#include "DataDef.h"
#include "Profiler.h"
#include "Log.h"
#include "DebugDraw.h"
//===================================
// RESOURCES
#include "Resource.h"
#include "Animation.h"
#include "IK.h"
#include "Ragdoll.h"
#include "AnimRig.h"
#include "AnimFSM.h"
//===================================
//=======================================================================================
#include <Common/Base/Container/Array/hkArray.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Animation/Animation/Playback/SampleAndBlend/hkaSampleBlendJobQueueUtils.h>
#include <Animation/Animation/Playback/SampleAndBlend/hkaSampleBlendJob.h>
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredAnimation.h>
#include <Animation/Animation/Animation/hkaAnimationBinding.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Visualize/hkDebugDisplay.h>
//=======================================================================================


AnimationSystem g_animMgr;

struct AnimJobs
{
    HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_USER, AnimJobs );
    hkArray<hkaSampleBlendJob> m_jobs;
};
AnimJobs*                               g_animJobs = 0;

void AnimationSystem::init()
{
    m_status = 0;
    hkaSampleBlendJobQueueUtils::registerWithJobQueue( g_threadMgr.getJobQueue());
    g_animJobs = new AnimJobs;
    g_animJobs->m_jobs.reserve(100);
}

void AnimationSystem::quit()
{
    SAFE_DELETE(g_animJobs);
}

void AnimationSystem::checkStatus()
{
    HK_ASSERT2(0, (m_status != kTickProcessing),  "AnimSystem Status is Processing!!!");
}

void AnimationSystem::frameStart()
{
    m_status = kTickFrameStart;
}

void AnimationSystem::kickInJobs()
{
    DynamicObjectArray<AnimRigInstance>& animList = g_animInstances.m_objects;
    uint32_t numSkeletons = animList.getSize();
    if(numSkeletons == 0)
        return;
    PROFILE(Animation_KickInJobs);
    m_status = kTickProcessing;
    hkArray<hkaSampleBlendJob>& jobs = g_animJobs->m_jobs;
    jobs.clear();
    jobs.setSize(numSkeletons);
    for (uint32_t i=0; i<numSkeletons;++i)
    {
        AnimRigInstance& instance = animList[i];
        g_animJobs->m_jobs[i].build(instance.m_skeleton, instance.m_pose, true);
    }
    hkLocalArray<hkJob*> jobPointers( numSkeletons );
    jobPointers.reserve( numSkeletons );
    for ( uint32_t i = 0; i < numSkeletons; ++i )
    {
        jobPointers.pushBack(&( jobs[i]));
    }
    g_threadMgr.getJobQueue()->addJobBatch( jobPointers, hkJobQueue::JOB_HIGH_PRIORITY );
}

void AnimationSystem::tickFinishJobs()
{
    if(g_animInstances.m_objects.getSize() == 0)
        return;
    PROFILE(AnimationFinishJobs);
    m_status = kTickProcessing;
    hkArray<hkaSampleBlendJob>& jobs = g_animJobs->m_jobs;
    for(int i=0; i<jobs.getSize();++i)
    {
        jobs[i].destroy();
    }
}


Id AnimationSystem::create_fsm(const AnimFSM* resource)
{
    AnimFSMInstance inst;
    inst.init(resource);
    return id_array::create(m_fsms, inst);
}

void AnimationSystem::destroy_fsm(Id id)
{
    if(!id_array::has(m_fsms, id)) return;
    AnimFSMInstance& inst = id_array::get(m_fsms, id);
    inst.destroy();
    id_array::destroy(m_fsms, id);
}

AnimFSMInstance* AnimationSystem::get_fsm(Id id)
{
    if(!id_array::has(m_fsms, id)) return 0;
    return &id_array::get(m_fsms, id);
}

Id AnimationSystem::create_rig(const AnimRig* resource)
{
    AnimRigInstance inst;
    inst.init(resource);
    return id_array::create(m_rigs, inst);
}

void AnimationSystem::destroy_rig(Id id)
{
    if(!id_array::has(m_rigs, id)) return;
    AnimRigInstance& inst = id_array::get(m_rigs, id);
    inst.destroy();
    id_array::destroy(m_rigs, id);
}


AnimRigInstance* AnimationSystem::get_rig(Id id)
{
    if(!id_array::has(m_rigs, id)) return 0;
    return &id_array::get(m_rigs, id);
}