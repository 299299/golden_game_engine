#include "Thread.h"
#include "Profiler.h"
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Thread/Pool/hkCpuThreadPool.h>
#include <Common/Visualize/hkVisualDebugger.h>
#include <Common/Base/System/Hardware/hkHardwareInfo.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>

ThreadSystem g_threadMgr;

ThreadSystem::ThreadSystem()
    :mJobQueue(NULL)
    ,mThreadPool(NULL)
    ,mPhysicsCtx(NULL)
    ,mVDB(NULL)
    ,mMainThreadId(0)
{
    mJobQueue = NULL;
    mThreadPool = NULL;
}

ThreadSystem::~ThreadSystem()
{

}

void ThreadSystem::init(bool bCreateVDB)
{
    mMainThreadId = ::GetCurrentThreadId();

    // Get the number of physical threads available on the system
    int totalNumThreadsUsed = hkHardwareInfo::getNumHardwareThreads();

    // We use one less than this for our thread pool, because we must also use this thread for our simulation
    hkCpuThreadPoolCinfo threadPoolCinfo;
    threadPoolCinfo.m_numThreads = totalNumThreadsUsed - 2;

    // This line enables timers collection, by allocating 200kb per thread.
    threadPoolCinfo.m_timerBufferPerThreadAllocation = 200 * 1024;
    mThreadPool = new hkCpuThreadPool( threadPoolCinfo );

    hkJobQueueCinfo info;
    info.m_jobQueueHwSetup.m_numCpuThreads = totalNumThreadsUsed;
    mJobQueue = new hkJobQueue(info);

    if(bCreateVDB)
    {
        hkArray<hkProcessContext*> contexts;
        mPhysicsCtx = new hkpPhysicsContext();
        hkpPhysicsContext::registerAllPhysicsProcesses();
        contexts.pushBack( mPhysicsCtx );
        mVDB = new hkVisualDebugger(contexts);
        mVDB->serve();
    }
}

void ThreadSystem::quit()
{
    if(mVDB)
    {
        hkMonitorStream::getInstance().reset();
        mThreadPool->clearTimerData();
        SAFE_REMOVEREF(mVDB);
        SAFE_REMOVEREF(mPhysicsCtx);
    }
    delete mJobQueue;
    SAFE_REMOVEREF(mThreadPool);
}

void ThreadSystem::processAllJobs()
{
    PROFILE(Thread_Process);
    mThreadPool->processJobQueue( mJobQueue );
    mJobQueue->processAllJobs( );
}

void ThreadSystem::wait()
{
    PROFILE(Thread_Wait);
    mThreadPool->waitForCompletion();
}

void ThreadSystem::vdbAddWorld( hkpWorld* pWorld )
{
    if(mPhysicsCtx)
        mPhysicsCtx->addWorld(pWorld);
}

void ThreadSystem::vdbRemoveWorld( hkpWorld* pWorld )
{
    if(mPhysicsCtx)
        mPhysicsCtx->removeWorld(pWorld);
}

void ThreadSystem::updateVDB( float timeStep )
{
    if(!mVDB)
        return;
    mPhysicsCtx->syncTimers( mThreadPool );
    mVDB->step(timeStep);
    hkMonitorStream::getInstance().reset();
    mThreadPool->clearTimerData();
}

bool ThreadSystem::checkMainThread() const
{
    return mMainThreadId == ::GetCurrentThreadId();
}