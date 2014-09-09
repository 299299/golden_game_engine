#include "Engine.h"
#include "Prerequisites.h"
//sub systems
#include "Memory.h"
#include "Thread.h"
#include "Resource.h"
#include "PhysicsWorld.h"
#include "AnimationSystem.h"
#include "XBoxInput.h"
#include "Graphics.h"
#include "MemoryPool.h"
#include "Profiler.h"
#include "EntityManager.h"
#include "GameFSM.h"
#include "Component.h"
#include "ScriptSystem.h"
//=================================================================
#include "Log.h"
#include "DataDef.h"
#include "Win32Context.h"
//=================================================================
#include <bx/timer.h>
#include <windows.h>

float     g_totalSeconds = 0.0;
double    g_frameTimeMS = 0.0; 
uint32_t  g_frameId = 0;
int       g_engineMode = 0;
uint32_t  g_frameLostNum = 0;
Engine    g_engine;

static void windowSizeCallback(uint32_t w, uint32_t h)
{
    Graphics::resize(w, h);
}

void Engine::init( const EngineConfig& cfg )
{
    m_running = true;
    m_updating = true;
    m_cfg = cfg;
    LOG_INIT("EngineLog.html", "ENGINE");
    HiresTimer::Init();
    coreInit();
    subSystemsInit();
    g_memoryMgr.dump();
}

void Engine::quit()
{
    subSystemsShutdown();
    coreShutdown();
    LOG_TERM();
}

void Engine::run()
{
    const double DT = 1.0/m_cfg.m_fixedFPS;
    const float fixTimeStep = (const float)DT;
    const double fixTimeMS = DT * 1000;
    HiresTimer m_timer;

    while (m_running)
    {
        PROFILE_BEGIN();
        g_win32Context.pollWin32Events();
        if(g_win32Context.isWindowClosed()) 
        {
            m_running = false;
            return;
        }
        m_timer.Reset();
        frame(fixTimeStep);
        double timeMS = (double)m_timer.GetUSec(false) / 1000.0;
        g_frameTimeMS = timeMS;
        g_totalSeconds += (float)(timeMS/1000.0);
        if(timeMS < fixTimeMS) applyFrameLimit(fixTimeMS - timeMS);
        else ++g_frameLostNum;
        PROFILE_END();
    }
}

void Engine::frame(float timeStep)
{
    //advance frame id.
    ++g_frameId;
    if(g_frameId >= 0xFFFFFFFE)
    {
        g_frameId = 0;
        LOGW("FrameId overflow!!");
    }

    g_memoryMgr.clear(kMemoryCategoryFrame);
    if(m_updating)
    {
        g_gameFSM.frameStart(timeStep);
        {
            PROFILE(Game_PreStep);
            g_gameFSM.preStep(timeStep);
        }
        {
            PROFILE(Game_Step);
            g_gameFSM.step(timeStep);
        }
        {
            PROFILE(Game_PostStep);
            g_gameFSM.postStep(timeStep);
        }
        g_gameFSM.frameEnd(timeStep);
        g_threadMgr.updateVDB(timeStep);
    }

    if(g_engineMode == 1)
        return;

    PROFILE(Game_Render);
    g_gameFSM.render();
}

void Engine::applyFrameLimit(double timeMS)
{
    PROFILE(FrameLimit);
    if(timeMS < 1.0) return;
    ::Sleep((DWORD)timeMS);
}

void Engine::coreInit()
{
    TIMELOG("Engine Core Init");
    g_memoryMgr.init(m_cfg.m_checkMemory);
    g_threadMgr.init(true);
    g_resourceMgr.init();
#ifdef USE_PROFILING
    g_profiler.Init();
#endif
}

void Engine::subSystemsInit()
{
    TIMELOG("Engine Subsystem Init");
    g_componentMgr.init();

    if(!m_cfg.m_headless)
        g_win32Context.createWindow(m_cfg.m_windowTitle, m_cfg.m_windowWidth, m_cfg.m_windowHeight);
    else
        g_engineMode = 1;

    Win32InputCallback cb = 
    {
        windowSizeCallback, 0, 0, 0
    };
    g_win32Context.registerCallback(cb);

    Graphics::init(g_win32Context.m_hwnd, m_cfg.m_fullScreen);
    g_physicsWorld.init();
    g_physicsWorld.createWorld(1000.0f, hkVector4(0, -9.8f, 0), true);
    g_animMgr.init();
    g_entityMgr.init();
    g_gameFSM.init();
    g_componentMgr.initFactories();
    g_script.init();
}

void Engine::coreShutdown()
{
    TIMELOG("Engine Core Shutdown");
    g_threadMgr.quit();
    g_memoryMgr.quit();
    g_win32Context.destroyWindow();
}

void Engine::subSystemsShutdown()
{
    TIMELOG("Engine Subsystem Shutdown");
    g_script.quit();
    g_componentMgr.destroy();
    g_gameFSM.quit();
    g_entityMgr.quit();
    g_animMgr.quit();
    g_physicsWorld.quit();
    g_resourceMgr.destroyAllResources();
    Graphics::quit();
    g_resourceMgr.quit();
}