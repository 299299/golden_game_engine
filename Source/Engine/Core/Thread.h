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
    
    hkJobQueue* get_jobqueue() const { return m_jobQueue;};
    hkThreadPool* get_threadpool() const { return m_threadPool;};
    uint32_t get_main_threadid() const { return m_mainThreadId; };
    bool check_main_thread() const;

    void process_all_jobs();
    void wait();

    void vdb_add_world(hkpWorld* pWorld);
    void vdb_remove_world(hkpWorld* pWord);
    void vdb_update(float timeStep);
private:
    hkJobQueue*                                     m_jobQueue;
    hkThreadPool*                                   m_threadPool;
    hkpPhysicsContext*                              m_physicsCtx;
    hkVisualDebugger*                               m_vdb;
    uint32_t                                        m_mainThreadId;
};

extern ThreadSystem g_threadMgr;