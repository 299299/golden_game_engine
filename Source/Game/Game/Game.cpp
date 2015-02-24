#include "Engine.h"
#include "Log.h"
#include "Profiler.h"
#include "MemorySystem.h"
#include "Utils.h"
#include "linear_allocator.h"
#include "Resource.h"
#include "DebugDraw.h"
#include "Graphics.h"
#include "Utils.h"
#include "PhysicsWorld.h"
#include "ShadingEnviroment.h"
#include "PreviewState.h"
#include "PlayerState.h"
#include "DataDef.h"
#include "Actor.h"
#include <bx/bx.h>
#include <bx/commandline.h>


ActorId32 g_previewActor = 0;
int game_main(int argc, bx::CommandLine* cmdline)
{
    if(cmdline->hasArg("compile"))
    {
        extern void run_data_compile();
        run_data_compile();
    }

    const char* package_name = 0;
    const char* state_name = 0;

    EngineConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_checkMemory = true;
    cfg.m_windowTitle = "game";
    cfg.m_windowWidth = 1280;
    cfg.m_windowHeight = 720;
    cfg.m_fixedFPS = 60;

    const char* name = cmdline->findOption('w');
    if(name) cfg.m_windowWidth = atoi(name);
    name = cmdline->findOption('h');
    if(name) cfg.m_windowHeight = atoi(name);
    cfg.m_headless = cmdline->hasArg("headless");
    name = cmdline->findOption('t');
    if(name) cfg.m_windowTitle = name;
    package_name = cmdline->findOption("package");
    state_name = cmdline->findOption("state");

    g_engine.init(cfg);
    g_gameFSM.add_state(new PreviewState);
    g_gameFSM.add_state(new PlayerState);

    bool _autoreload = cmdline->hasArg("autoreload");
    if(_autoreload)
    {
        extern void resource_hot_reload_init();
        resource_hot_reload_init();
    }

    if(!g_resourceMgr.load_package_and_wait("data/core.package"))
    {
        msg_box("data/core.package load failed");
        goto err;
    }

    Graphics::ready();
    g_debugDrawMgr.ready();
    g_physicsWorld.create_world(
        (PhysicsConfig*)g_resourceMgr.find_resource(
        EngineTypes::PHYSICS_CONFIG,
        stringid_caculate("core/global"))
        );
    g_physicsWorld.create_plane(500.0f);
    g_actorWorld.m_shading_env = (ShadingEnviroment*)(g_resourceMgr.find_resource(
        EngineTypes::SHADING_ENV,
        stringid_caculate("core/common/default")));

    if(package_name)
        g_resourceMgr.load_package_and_wait(package_name);

    if(state_name)
        g_gameFSM.change_state(state_name);

    GameState* _state = g_gameFSM.get_state();
    if(_state)
        _state->process_cmd_args(&cmdline);
    

    g_engine.run();

err:
    //------------------------------------------------------------
#if 0
    g_profiler.dump_to_file("game_profile.txt", true, true);
#endif

    if(_autoreload)
    {
        extern void resource_hot_reload_shutdown();
        resource_hot_reload_shutdown();
    }

    //------------------------------------------------------------
    g_engine.quit();
    return 0;
}