#include "Engine.h"
#include "Prerequisites.h"
#include "MemorySystem.h"
#include "Thread.h"
#include "Resource.h"
#include "PhysicsWorld.h"
#include "AnimationSystem.h"
#include "XBoxInput.h"
#include "Graphics.h"
#include "Profiler.h"
#include "Utils.h"
#include "GameConfig.h"
#include "GameState.h"
#include "DebugDraw.h"
#include "Log.h"
#include "DataDef.h"
#include "Win32Context.h"
#include "Actor.h"
#include <bx/timer.h>

float     g_totalSeconds = 0.0;
double    g_frameTimeMS = 0.0;
uint32_t  g_frameId = 0;
int       g_engineMode = 0;
uint32_t  g_frameLostNum = 0;
Engine    g_engine;

void Engine::init( const EngineConfig& cfg )
{
    m_running = true;
    m_cfg = cfg;
    m_state = kFrameStart;
    LOG_INIT("EngineLog.html", "ENGINE");
    core_init();
    subsystem_init();
    g_gameFSM.init();
}

void Engine::quit()
{
    g_gameFSM.quit();
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
            PROFILE_END();
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

    {
        PROFILE(Engine_FrameStart);
        m_state = kFrameStart;
        g_memoryMgr.frame_start();
        Graphics::frame_start();
        g_physicsWorld.frame_start();
        g_animMgr.frame_start();
    }

    {
        PROFILE(Engine_PreStep);
        m_state = kFramePreStepping;
        g_gameFSM.pre_step(timeStep);
    }
    {
        PROFILE(Engine_Step);
        g_physicsWorld.kick_in_jobs(timeStep);
        g_animMgr.kick_in_jobs();
        g_threadMgr.process_all_jobs();
        //------------------------------------
        m_state = kFrameUpdating;
        g_gameFSM.step(timeStep);
        //------------------------------------
        g_threadMgr.wait();
        g_physicsWorld.tick_finished_jobs();
        g_animMgr.tick_finished_jobs();
    }
    {
        PROFILE(Engine_PostStep);
        m_state = kFramePostStepping;
        g_gameFSM.post_step(timeStep);
    }

    {
        PROFILE(Engine_Render);
        m_state = kFrameRendering;
        g_gameFSM.render();
    }

    {
        PROFILE(Engine_FrameEnd);
        m_state = kFrameEnd;
        Graphics::frame_end();
        g_threadMgr.vdb_update(timeStep);
    }
}

void Engine::apply_framelimit(double timeMS)
{
    PROFILE(FrameLimit);
    if(timeMS < 1.0) return;
    accurate_sleep((uint32_t)timeMS);
}

void Engine::core_init()
{
    TIMELOG("Engine Core Init");
    MemoryConfig cfg;
    cfg.m_checkHavokMem = m_cfg.m_checkMemory;
    cfg.m_debugMemSize = DEBUG_MEMORY_SIZE;
    cfg.m_frameMemSize = FRAME_MEMORY_SIZE;
    cfg.m_havokFrameMemSize = HAVOK_FRAMEMEMORY_SIZE;
    cfg.m_havokMonitorMemSize = HAVOK_MONITOR_MEM_SIZE;
    cfg.m_initHavok = true;
    g_memoryMgr.init(cfg);
    g_threadMgr.init(true);
    g_profiler.init(TOTAL_BLOCK_NUM);
    g_resourceMgr.init();
}

void Engine::subsystem_init()
{
    TIMELOG("Engine Subsystem init");

    if(!m_cfg.m_headless) g_win32Context.create_window(m_cfg.m_windowTitle, m_cfg.m_windowWidth, m_cfg.m_windowHeight);
    else g_engineMode = 1;

    Graphics::register_factories();
    PhysicsWorld::register_factories();
    AnimationSystem::register_factories();
    ActorWorld::register_factories();

    Graphics::init(g_win32Context.m_hwnd, m_cfg.m_fullScreen);
    g_physicsWorld.init(MAX_PHYSICS, MAX_PROXY);

    AnimationConfig cfg1;
    memset(&cfg1, 0x00, sizeof(cfg1));
    cfg1.max_rigs = MAX_ANIM_RIG;
    cfg1.max_anim_events = MAX_ANIM_EVENTS;
    cfg1.max_state_layers = MAX_ANIM_FSM;
    g_animMgr.init(cfg1);

    ActorConfig cfg2;
    memset(&cfg2, 0x00, sizeof(cfg2));
    cfg2.max_characters = MAX_CHARACTER;
    cfg2.max_geometries = MAX_LEVEL_GEOMETRY;
    cfg2.max_props = MAX_PROP;
    g_actorWorld.init(cfg2);
}

void Engine::core_shutdown()
{
    TIMELOG("Engine Core Shutdown");
    g_profiler.shutdown();
    g_threadMgr.shutdown();
    g_memoryMgr.shutdown();
    g_win32Context.destroy_window();
}

void Engine::subsystem_shutdown()
{
    TIMELOG("Engine Subsystem Shutdown");
    g_actorWorld.shutdown();
    g_resourceMgr.offline_all_resources();
    g_animMgr.shutdown();
    g_physicsWorld.shutdown();
    Graphics::shutdown();
    g_debugDrawMgr.shutdown();
    g_resourceMgr.shutdown();
}
