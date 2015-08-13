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
#include "ToolUtils.h"
#include <bx/timer.h>

float     g_totalSeconds = 0.0;
double    g_frameTimeMS = 0.0;
uint32_t  g_frameId = 0;
int       g_engineMode = 0;
float     g_timeScale = 1.0f;
Engine    g_engine = { 0 };

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
        frame(fixTimeStep * g_timeScale);
        double timeMS = (double)m_timer.get_usec(false) / 1000.0;
        g_frameTimeMS = timeMS;
        g_totalSeconds += (float)(timeMS/1000.0);
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
        g_physicsWorld.kickin_jobs(timeStep);
        g_animMgr.kickin_jobs();
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

void Engine::core_init()
{
    TIMELOG("Engine Core Init");
    MemoryConfig cfg;
    cfg.m_checkHavokMem = m_game_cfg.m_havok_check_memory;
    cfg.m_debugMemSize = m_game_cfg.m_debug_memory_size;
    cfg.m_frameMemSize = m_game_cfg.m_frame_memory_size;
    cfg.m_havokFrameMemSize = m_game_cfg.m_havok_frame_memory_size;
    cfg.m_havokMonitorMemSize = m_game_cfg.m_havok_monitor_memory_size;
    cfg.m_initHavok = true;
    g_memoryMgr.init(cfg);
    g_threadMgr.init(true);
    g_profiler.init(TOTAL_BLOCK_NUM);
    g_resourceMgr.init();
    register_engine_factories();
}

void Engine::subsystem_init()
{
    TIMELOG("Engine Subsystem init");

    if(!m_cfg.m_headless)
        g_win32Context.create_window(m_cfg.m_windowTitle, m_cfg.m_windowPosSize[2], m_cfg.m_windowPosSize[3], m_cfg.m_windowPosSize[0], m_cfg.m_windowPosSize[1]);
    else
        g_engineMode = 1;

    Graphics::init(g_win32Context.m_hwnd, m_cfg.m_fullScreen);

    {
        // physics
        g_physicsWorld.init(m_game_cfg.m_max_physics_objects, m_game_cfg.m_max_proxy_objects);
    }

    {
        //animation
        AnimationConfig cfg;
        memset(&cfg, 0x00, sizeof(cfg));
        cfg.max_rigs = m_game_cfg.m_max_rigs;
        cfg.max_anim_events = m_game_cfg.m_max_anim_evts;
        cfg.max_state_layers = m_game_cfg.m_max_anim_fsm;
        g_animMgr.init(cfg);
    }

    {
        //actor
        ActorConfig cfg;
        memset(&cfg, 0x00, sizeof(cfg));
        cfg.max_characters = m_game_cfg.m_max_characters;
        cfg.max_geometries = m_game_cfg.m_max_geometries;
        cfg.max_props = m_game_cfg.m_max_props;
        g_actorWorld.init(cfg);
    }
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

bool Engine::load_game_cfg(const char* cfg_file)
{
    jsonxx::Object o;
    if (!read_json_from_file(o, cfg_file))
        return false;

    memset (&m_game_cfg, 0x00, sizeof(m_game_cfg));

    m_game_cfg.m_max_models = json_to_int(o, "max_models");
    m_game_cfg.m_max_lights = json_to_int(o, "max_lights");
    m_game_cfg.m_max_rigs = json_to_int(o, "max_rigs");
    m_game_cfg.m_max_anim_evts = json_to_int(o, "max_anim_evts");
    m_game_cfg.m_max_anim_fsm = json_to_int(o, "max_anim_fsm");
    m_game_cfg.m_max_characters = json_to_int(o, "max_characters");
    m_game_cfg.m_max_geometries = json_to_int(o, "max_geometries");
    m_game_cfg.m_max_props = json_to_int(o, "max_props");
    m_game_cfg.m_max_physics_objects = json_to_int(o, "max_physics_objects");
    m_game_cfg.m_max_proxy_objects = json_to_int(o, "max_proxy_objects");
    m_game_cfg.m_max_raycast_per_frame = json_to_int(o, "max_raycast_per_frame");

    m_game_cfg.m_debug_memory_size = SIZE_MB(json_to_int(o, "debug_memory_size"));
    m_game_cfg.m_frame_memory_size = SIZE_MB(json_to_int(o, "frame_memory_size"));
    m_game_cfg.m_havok_monitor_memory_size = SIZE_MB(json_to_int(o, "havok_monitor_memory_size"));
    m_game_cfg.m_havok_frame_memory_size = SIZE_MB(json_to_int(o, "havok_frame_memory_size"));

    m_game_cfg.m_havok_check_memory = json_to_bool(o, "havok_check_memory");

    return true;
}

void register_engine_factories()
{
    Graphics::register_factories();
    PhysicsWorld::register_factories();
    AnimationSystem::register_factories();
    ActorWorld::register_factories();
}
