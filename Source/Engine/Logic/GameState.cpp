#include "GameState.h"
//========================================
//sub systems
#include "PhysicsWorld.h"
#include "AnimationSystem.h"
#include "XBoxInput.h"
#include "Graphics.h"
#include "WebServerTool.h"
#include "Profiler.h"
#include "EntityManager.h"
#include "DataDef.h"
#include "Thread.h"
#include "Memory.h"
#include "ShadingEnviroment.h"

GameState::GameState()
:m_timeInState(0)
,m_shading(0)
,m_hasEntered(false)
{

}

void GameState::onEnter(GameState* pPrevState)
{
    m_timeInState = 0.0f;
    if(!m_hasEntered) onFirstEnter(pPrevState);
    m_hasEntered = true;
}

void GameState::frameStart(float timeStep)
{
    g_animMgr.frameStart();
    g_physicsWorld.frameStart();
    Graphics::frameStart();
    g_XInput.update(timeStep);
}

void GameState::preStep(float timeStep)
{
    m_timeInState += timeStep;
    g_entityMgr.preStep(timeStep);
    g_animMgr.kickInJobs();
    g_physicsWorld.kickInJobs(timeStep);
    if(m_shading) Graphics::cull(m_shading->m_shadowAreaSize, m_shading->m_shadowFar);
}

void GameState::step(float timeStep)
{
    g_threadMgr.processAllJobs();
    g_threadMgr.wait();
    g_physicsWorld.tickFinishJobs(timeStep);
    g_animMgr.tickFinishJobs();
}

void GameState::postStep(float timeStep)
{
    g_entityMgr.postStep(timeStep);
    Graphics::update(timeStep);
    dbgPrintfEngineStatus();
}

void GameState::render()
{
    Graphics::draw(m_shading);
}

void GameState::frameEnd(float timeStep)
{
    Graphics::frameEnd();
}

void GameState::dbgPrintfEngineStatus( bool bDumpProfiler)
{
    extern  double      g_frameTimeMS;
    extern  uint32_t    g_frameLostNum;
    extern  uint32_t    g_frameId;
    DBG_TEX_PRINTF(0x4f, "frame-time=%g[MS], frame-id=%u, frame-lost=%u", g_frameTimeMS, g_frameId, g_frameLostNum);
    DBG_TEX_PRINTF(0x6f, "memory static=%d[KB], frame=%d[KB], havok=%d[KB], debug=%d[KB]", 
        g_memoryMgr.allocedSize(kMemoryCategoryStatic)/1000, 
        g_memoryMgr.allocedSize(kMemoryCategoryFrame)/1000,
        g_memoryMgr.allocedSize(kMemoryCategoryDebug)/1000);
    if(bDumpProfiler) g_profiler.Dump();
}
