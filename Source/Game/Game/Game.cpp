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
#include "Actor.h"
#include <bx/bx.h>
#include <bx/commandline.h>

int game_main(int argc, bx::CommandLine* cmdline)
{
    const char* actor_name = 0;
    const char* level_name = 0;
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
    name = cmdline->findOption("actor");
    if(name) actor_name = name;
    name = cmdline->findOption("level");
    if(name) level_name = name;
    name = cmdline->findOption('t');
    if(name) cfg.m_windowTitle = name;
    package_name = cmdline->findOption("package");
    state_name = cmdline->findOption("state");

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
    g_actorWorld.m_shading_env = FIND_RESOURCE_NAMED(ShadingEnviroment, "core/common/default");

    if(package_name) 
        g_resourceMgr.load_package_and_wait(package_name);

    if(actor_name) 
    {
        LOGD("loading actor %s \n", actor_name);
        hkQsTransform t;
#ifdef HAVOK_COMPILE
        t.setIdentity();
#endif
        ActorId32 actor = g_actorWorld.create_actor(StringId(actor_name), t);
        LOGD("created actor = %d", actor);
    }
    if(level_name)
    {
        LOGD("loading level %s \n", level_name);
        Level* level = FIND_RESOURCE_NAMED(Level, level_name);
        if(level) level->load();
    }

    if(state_name) g_gameFSM.change_state(state_name);

    g_engine.run();

err:
    //------------------------------------------------------------
    g_profiler.dump_to_file("game_profile.txt", true, true);
    //------------------------------------------------------------
    g_engine.quit();
    return 0;
}