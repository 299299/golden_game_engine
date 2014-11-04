#include "Engine.h"
#include "Log.h"
#include "Profiler.h"
#include "WebServerTool.h"
#include "MemorySystem.h"
#include "Utils.h"
#include "linear_allocator.h"
#include "Resource.h"
#include "DebugDraw.h"
#include "Graphics.h"
#include "Utils.h"
#include "Actor.h"
#include "Level.h"
#include "AnimRig.h"
#include "PhysicsWorld.h"
#include "ShadingEnviroment.h"
#include "Camera.h"
//==================================================
#include <Windows.h>
#include <tchar.h>
#include <bx/bx.h>
#include <bx/commandline.h>

void showHelp()
{
    printf("Usage: Game [options]\n"
            "Options:\n"
            "-w set window width\n"
            "-h set window height\n"
            "-t set window title\n"
            "--package --> package to load\n"
            "--actor --> actor name\n"
            "--level --> level name\n"
            "--animation --> animation name\n"
            "--websocket wait for debug attach when launched.\n"
            "--debug wait for debug attach when launched.\n"
            "--headless no graphics & no window\n");
}

#define MUTEX_NAME     _T("Global//NAGA_ENGINE_GAME_SINGLE_MUTEX")
BOOL checkSingleProcess()
{
    HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ::CloseHandle(hMutex);
        return FALSE;
    }
    else return TRUE;
}

ActorId32 g_actor;
int _tmain(int argc, _TCHAR* argv[])
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

    EngineConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_checkMemory = true;
    cfg.m_windowTitle = "naga_engine";
    cfg.m_windowWidth = 1280;
    cfg.m_windowHeight = 720;
    cfg.m_fixedFPS = 60;
    extern void game_pre_step(float);
    extern void game_step(float);
    extern void game_post_step(float);
    extern void game_render(float);
    cfg.m_preStepHook = game_pre_step;
    cfg.m_stepHook = game_step;
    cfg.m_postStepHook = game_post_step;
    cfg.m_renderHook = game_render;

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

    if(cmdline.hasArg("debug")) msg_box("wait for visual studio attach process.", "ENGINE");

    if(cmdline.hasArg("websocket"))
    {
        if(checkSingleProcess() == FALSE)
        {
            msg_box("process already exist!", "ENGINE");
            return 0;
        }
        printf("\n\n------ create web socket ----\n\n");
        initWebServerTool(6161);
        extern void init_remote_commands();
        init_remote_commands();
    }

    extern void register_memory_allocators();
    register_memory_allocators();

    g_engine.init(cfg);

    extern void resource_hot_reload_init();
    resource_hot_reload_init();

    g_resourceMgr.load_package_and_wait("data/core.package");

    Graphics::ready();
    g_debugDrawMgr.ready();
    g_physicsWorld.create_world(FIND_RESOURCE_NAMED(PhysicsConfig, "core/global"));
    g_physicsWorld.create_plane(500.0f);
    g_actorWorld.m_shading_env = FIND_RESOURCE_NAMED(ShadingEnviroment, "core/common/default");
    float eye[] = {-5,5,0};
    float at[] = {0,0,0};
    g_camera.update(eye, at);

    if(package_name) g_resourceMgr.load_package_and_wait(package_name);

    if(actor_name) 
    {
        printf("loading actor %s \n", actor_name);
        g_actor = g_actorWorld.create_actor(
                    FIND_RESOURCE_NAMED(ActorResource, actor_name), 
                    hkQsTransform::getIdentity());
    }
    if(level_name)
    {
        printf("loading level %s \n", level_name);
        Level* level = FIND_RESOURCE_NAMED(Level, level_name);
        if(level) level->load();
    }

    const char* anim_name = cmdline.findOption("animation");
    if(anim_name && actor_name)
    {
        Actor* actor = g_actorWorld.get_actor(g_actor);
        if(actor)
        {
            LOGI("loading animation %s to actor %s", anim_name, actor_name);
            extern void* get_anim_rig(Id);
            AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(actor->m_components[kComponentAnimRig]);
            if(rig)
            {
               rig->test_animation(anim_name);
            }
        }
    }

    g_engine.run();
    quitWebServerTool();

    //------------------------------------------------------------
    g_engine.quit();
    //------------------------------------------------------------
    g_profiler.dump_to_file("game_profile.txt", true, true);
    return 0;
}

//===========================================================
static char             g_frameBuf[1024*1024*5];//5M Frame Mem
static LinearAllocator  g_frameAllocator(g_frameBuf, sizeof(g_frameBuf));

void register_memory_allocators()
{
    g_memoryMgr.register_allocator(kMemoryCategoryFrame, &g_frameAllocator);
}
