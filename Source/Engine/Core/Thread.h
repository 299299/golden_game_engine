#pragma once
#include "Prerequisites.h"

class hkJobQueue;
class hkJobThreadPool;
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
    
    hkJobQueue* getJobQueue() const { return mJobQueue;};
    hkJobThreadPool* getThreadPool() const { return mThreadPool;};
    uint32_t getMainThreadId() const { return mMainThreadId; };
    bool checkMainThread() const;

    void processAllJobs();
    void wait();

    void vdbAddWorld(hkpWorld* pWorld);
    void vdbRemoveWorld(hkpWorld* pWord);
    void updateVDB(float timeStep);
private:
    hkJobQueue*                                     mJobQueue;
    hkJobThreadPool*                                mThreadPool;

    hkpPhysicsContext*                              mPhysicsCtx;
    hkVisualDebugger*                               mVDB;
    uint32_t                                        mMainThreadId;
};

extern ThreadSystem g_threadMgr;