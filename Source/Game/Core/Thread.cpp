#include "Thread.h"
#include "Prerequisites.h"
#include "Profiler.h"
#ifdef HAVOK_COMPILE
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Thread/Pool/hkCpuThreadPool.h>
#include <Common/Visualize/hkVisualDebugger.h>
#include <Common/Base/System/Hardware/hkHardwareInfo.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>
#endif

ThreadSystem g_threadMgr;

ThreadSystem::ThreadSystem()
    :m_jobQueue(NULL)
    ,m_threadPool(NULL)
    ,m_physicsCtx(NULL)
    ,m_vdb(NULL)
    ,m_mainThreadId(0)
{
}

ThreadSystem::~ThreadSystem()
{

}

void ThreadSystem::init(bool bCreateVDB)
{
    m_mainThreadId = bx::getTid();
#ifdef HAVOK_COMPILE
    // Get the number of physical threads available on the system
    int totalNumThreadsUsed = hkHardwareInfo::getNumHardwareThreads();

    // We use one less than this for our thread pool, because we must also use this thread for our simulation
    hkCpuThreadPoolCinfo threadPoolCinfo;
    threadPoolCinfo.m_numThreads = totalNumThreadsUsed - 2;

    // This line enables timers collection, by allocating 200kb per thread.
    threadPoolCinfo.m_timerBufferPerThreadAllocation = 200 * 1024;
    m_threadPool = new hkCpuThreadPool( threadPoolCinfo );

    hkJobQueueCinfo info;
    info.m_jobQueueHwSetup.m_numCpuThreads = totalNumThreadsUsed;
    m_jobQueue = new hkJobQueue(info);

    if(bCreateVDB)
    {
        hkArray<hkProcessContext*> contexts;
        m_physicsCtx = new hkpPhysicsContext();
        hkpPhysicsContext::registerAllPhysicsProcesses();
        contexts.pushBack( m_physicsCtx );
        m_vdb = new hkVisualDebugger(contexts);
        m_vdb->serve();
    }
#endif
}

void ThreadSystem::quit()
{
#ifdef HAVOK_COMPILE
    if(m_vdb)
    {
        hkMonitorStream::getInstance().reset();
        m_threadPool->clearTimerData();
        SAFE_REMOVEREF(m_vdb);
        SAFE_REMOVEREF(m_physicsCtx);
    }
    SAFE_DELETE(m_jobQueue);
    SAFE_REMOVEREF(m_threadPool);
#endif
}

void ThreadSystem::process_all_jobs()
{
    PROFILE(Thread_Process);
#ifdef HAVOK_COMPILE
    m_threadPool->processJobQueue(m_jobQueue);
    m_jobQueue->processAllJobs();
#endif
}

void ThreadSystem::wait()
{
    PROFILE(Thread_Wait);
#ifdef HAVOK_COMPILE
    m_threadPool->waitForCompletion();
#endif
}

void ThreadSystem::vdb_add_world( hkpWorld* pWorld )
{
#ifdef HAVOK_COMPILE
    if(m_physicsCtx) m_physicsCtx->addWorld(pWorld);
#endif
}

void ThreadSystem::vdb_remove_world( hkpWorld* pWorld )
{
#ifdef HAVOK_COMPILE
    if(m_physicsCtx) m_physicsCtx->removeWorld(pWorld);
#endif
}

void ThreadSystem::vdb_update( float timeStep )
{
    if(!m_vdb) return;
#ifdef HAVOK_COMPILE
    m_physicsCtx->syncTimers( m_threadPool );
    m_vdb->step(timeStep);
    hkMonitorStream::getInstance().reset();
    m_threadPool->clearTimerData();
#endif
}

bool ThreadSystem::check_main_thread() const
{
    return m_mainThreadId == bx::getTid();
}