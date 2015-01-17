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
#include "Level.h"
#include "AnimRig.h"
#include "PhysicsWorld.h"
#include "ShadingEnviroment.h"
#include "PreviewState.h"
#include "PlayerState.h"
#include "RenderCamera.h"
//==================================================
#include <bx/bx.h>
#include <bx/commandline.h>
#ifdef HAVOK_COMPILE
#include <Windows.h>
#endif

void showHelp()
{
    printf("Usage: Game [options]\n"
            "Options:\n"
            "-w set window width\n"
            "-h set window height\n"
            "-t set window title\n"
            "--package --> package to load\n"
            "--state --> game state to run\n"
            "--actor --> actor name\n"
            "--level --> level name\n"
            "--animation --> animation name\n"
            "--debug wait for debug attach when launched.\n"
            "--headless no graphics & no window\n");
}

ActorId32 g_actor;
int main(int argc, char* argv[])
{
#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
    // Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
    // Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

    showHelp();

    const char* actor_name = 0;
    const char* level_name = 0;
    const char* package_name = 0;
    const char* script = 0;
    const char* state_name = 0;

    EngineConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_checkMemory = true;
    cfg.m_windowTitle = "naga_engine";
    cfg.m_windowWidth = 1280;
    cfg.m_windowHeight = 720;
    cfg.m_fixedFPS = 60;

    bx::CommandLine cmdline(argc, argv);

    const char* name = cmdline.findOption('w');
    if(name) cfg.m_windowWidth = atoi(name);
    name = cmdline.findOption('h');
    if(name) cfg.m_windowHeight = atoi(name);
    cfg.m_headless = cmdline.hasArg("headless");
    name = cmdline.findOption("actor");
    if(name) actor_name = name;
    name = cmdline.findOption("level");
    if(name) level_name = name;
    name = cmdline.findOption('t');
    if(name) cfg.m_windowTitle = name;
    script = cmdline.findOption("script");
    package_name = cmdline.findOption("package");
    state_name = cmdline.findOption("state");

    if(cmdline.hasArg("debug")) msg_box("wait for visual studio attach process.");

    g_engine.init(cfg);
    g_gameFSM.add_state(new PreviewState);
    g_gameFSM.add_state(new PlayerState);

    extern void resource_hot_reload_init();
    resource_hot_reload_init();

    if(!g_resourceMgr.load_package_and_wait("data/core.package"))
    {
        msg_box("data/core.package load failed");
        goto err;
    }

    Graphics::ready();
    g_debugDrawMgr.ready();
    g_physicsWorld.create_world(FIND_RESOURCE_NAMED(PhysicsConfig, "core/global"));
    g_physicsWorld.create_plane(500.0f);

    if(package_name) g_resourceMgr.load_package_and_wait(package_name);

    if(level_name)
    {
        printf("loading level %s \n", level_name);
        Level* level = FIND_RESOURCE_NAMED(Level, level_name);
        if(level) level->load();
    }

    if(state_name) g_gameFSM.change_state(state_name);

    g_engine.run();

err:
    //------------------------------------------------------------
    g_engine.quit();
    //------------------------------------------------------------
    g_profiler.dump_to_file("game_profile.txt", true, true);
    return 0;
}