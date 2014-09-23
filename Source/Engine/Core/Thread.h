#pragma once
#include "Prerequisites.h"

class hkJobQueue;
class hkThreadPool;
class hkpPhysicsContext;
class hkVisualDebugger;
class hkpWorld;

class ThreadSystem
{
public:
    ThreadSystem();
    ~ThreadSystem();
    void init(bool bCreateVDB);
    void quit();
    
    hkJobQueue* get_jobqueue() const { return mJobQueue;};
    hkThreadPool* get_threadpool() const { return mThreadPool;};
    uint32_t get_main_threadid() const { return mMainThreadId; };
    bool check_main_thread() const;

    void process_all_jobs();
    void wait();

    void vdb_add_world(hkpWorld* pWorld);
    void vdb_remove_world(hkpWorld* pWord);
    void vdb_update(float timeStep);
private:
    hkJobQueue*                                     mJobQueue;
    hkThreadPool*                                   mThreadPool;
    hkpPhysicsContext*                              mPhysicsCtx;
    hkVisualDebugger*                               mVDB;
    uint32_t                                        mMainThreadId;
};

extern ThreadSystem g_threadMgr;