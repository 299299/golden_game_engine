#include "Engine.h"
#include "Prerequisites.h"
//sub systems
#include "MemorySystem.h"
#include "Thread.h"
#include "Resource.h"
#include "PhysicsWorld.h"
#include "AnimationSystem.h"
#include "XBoxInput.h"
#include "Graphics.h"
#include "Profiler.h"
#include "Script.h"
#include "Actor.h"
#include "WebServerTool.h"
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

void Engine::init( const EngineConfig& cfg )
{
    m_running = true;
    m_updating = true;
    m_cfg = cfg;
    LOG_INIT("EngineLog.html", "ENGINE");
    HiresTimer::init();
    core_init();
    subsystem_init();
}

void Engine::quit()
{
    subsystem_shutdown();
    core_shutdown();
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
        g_win32Context.frame_start();
        if(g_win32Context.is_window_closed()) 
        {
            m_running = false;
            return;
        }
        m_timer.reset();
        frame(fixTimeStep);
        double timeMS = (double)m_timer.get_usec(false) / 1000.0;
        g_frameTimeMS = timeMS;
        g_totalSeconds += (float)(timeMS/1000.0);
        if(timeMS < fixTimeMS) apply_framelimit(fixTimeMS - timeMS);
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

    g_memoryMgr.frame_start();
    frame_start_websocket(timeStep);
    Graphics::frame_start();
    g_physicsWorld.frame_start();
    g_animMgr.frame_start();
    g_actorWorld.frame_start(timeStep);

    if(m_updating)
    {
        {
            PROFILE(Game_PreStep);
            g_actorWorld.pre_step(timeStep);
        }
        {
            PROFILE(Game_Step);
            g_physicsWorld.kick_in_jobs(timeStep);
            g_animMgr.kick_in_jobs();
            g_threadMgr.process_all_jobs();
            //------------------------------------
            g_actorWorld.step(timeStep);
            g_script.update(timeStep);
            //------------------------------------
            g_threadMgr.wait();
            g_physicsWorld.tick_finished_jobs();
            g_animMgr.tick_finished_jobs();
        }
        {
            PROFILE(Game_PostStep);
            g_actorWorld.post_step(timeStep);
        }
    }

    Graphics::frame_end();
    g_script.frame_end(timeStep);
    g_threadMgr.vdb_update(timeStep);

    if(g_engineMode == 0)
    {
        PROFILE(Game_Render);
        g_actorWorld.draw();
    }
}

void Engine::apply_framelimit(double timeMS)
{
    PROFILE(FrameLimit);
    if(timeMS < 1.0) return;
    ::Sleep((DWORD)timeMS);
}

void Engine::core_init()
{
    TIMELOG("Engine Core Init");
    PROFILE_INIT();
    g_memoryMgr.init(1024*1024*4, 1024*1024*2, true, m_cfg.m_checkMemory);
    g_threadMgr.init(true);
    g_resourceMgr.init();
}

void Engine::subsystem_init()
{
    TIMELOG("Engine Subsystem init");
    extern void regster_resource_factories();
    regster_resource_factories();

    if(!m_cfg.m_headless) g_win32Context.create_window(m_cfg.m_windowTitle, m_cfg.m_windowWidth, m_cfg.m_windowHeight);
    else g_engineMode = 1;

    Graphics::init(g_win32Context.m_hwnd, m_cfg.m_fullScreen);
    g_physicsWorld.init();
    g_animMgr.init();
    g_script.init();
    g_actorWorld.init();
}

void Engine::core_shutdown()
{
    TIMELOG("Engine Core Shutdown");
    g_threadMgr.quit();
    g_memoryMgr.quit();
    g_win32Context.destroy_window();
}

void Engine::subsystem_shutdown()
{
    TIMELOG("Engine Subsystem Shutdown");
    g_resourceMgr.offline_all_resources();
    g_actorWorld.destroy();
    g_script.quit();
    g_animMgr.quit();
    g_physicsWorld.quit();
    Graphics::quit();
    g_resourceMgr.quit();
}
