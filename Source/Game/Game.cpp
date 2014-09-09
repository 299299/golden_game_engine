#include "Engine.h"
#include "Log.h"
#include "Component.h"
#include "WebServerTool.h"
#include "Memory.h"
#include "MemoryPool.h"
#include "Utils.h"
//==================================================
//RESOURCE
#include "Resource.h"
#include "Animation.h"
#include "PhysicsInstance.h"
#include "ProxyInstance.h"
#include "AnimRig.h"
#include "IK.h"
#include "Ragdoll.h"
#include "Entity.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Light.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ShadingEnviroment.h"
#include "AnimFSM.h"
#include "Level.h"
//==================================================
#include "PhysicsWorld.h"
#include "AnimationSystem.h"
#include "Scene.h"
#include "LevelGeometry.h"
#include "Prop.h"
#include "Character.h"
//==================================================

#include "GameFSM.h"
#include "LoadingState.h"
#include "RemoteViewerState.h"
#include "RenderViewerState.h"
#include "TestGameState.h"
#include <Windows.h>
#include <tchar.h>
#include <bx/bx.h>
#include <bx/commandline.h>


void msgBox(const char* text, const char* title)
{
    ::MessageBoxA(NULL, text, title, MB_TOPMOST);
}

void showHelp()
{
    printf("Usage: Game [options]\n"
            "Options:\n"
            "-m set game mode(0-test, 1-remote, 2-render)\n"
            "-w set window width\n"
            "-h set window height\n"
            "--entity previewer --> entity name\n"
            "--level previewer --> level name\n"
            "--debug wait for debug attach when launched.\n"
            "--headless no graphics & no window\n");
}

#define MUTEX_NAME     _T("Global//GOLDEN_ENGINE_GAME_SINGLE_MUTEX")
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

void registerMemoryAllocators();

int _tmain(int argc, _TCHAR* argv[])
{
#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
    // Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
    // Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

    showHelp();

    const char* loadEntityName = 0;
    const char* loadLevelName = 0;

    EngineConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_checkMemory = true;    
    cfg.m_mode = 0;
    cfg.m_windowTitle = "Engine";
    cfg.m_windowWidth = 1280;
    cfg.m_windowHeight = 720;
    cfg.m_fixedFPS = 60;
    bx::CommandLine cmdline(argc, argv);
    
    const char* name = cmdline.findOption('m');
    if(name) cfg.m_mode = atoi(name);
    name = cmdline.findOption('w');
    if(name) cfg.m_windowWidth = atoi(name);
    name = cmdline.findOption('h');
    if(name) cfg.m_windowHeight = atoi(name);
    cfg.m_headless = cmdline.hasArg("headless");
    name = cmdline.findOption("entity");
    if(name) loadEntityName = name;
    name = cmdline.findOption("level");
    if(name) loadLevelName = name;
    if(cmdline.hasArg("debug")) msgBox("wait for visual studio attach process.", "ENGINE");

    if(cfg.m_mode == 1)
    {
        if(checkSingleProcess() == FALSE)
        {
            msgBox("process already exist!", "ENGINE");
            return 0;
        }
        initWebServerTool(6161);
    }

    static const char* window_names[] =
    {
        "test-game", "remote-viewer", "render-viewer",
    };
    cfg.m_webServer = cfg.m_mode == 1;
    cfg.m_windowTitle = window_names[cfg.m_mode];

    registerMemoryAllocators();
    g_engine.init(cfg);
    extern void registerResourceFactories();
    registerResourceFactories();

    LoadingState* loadingState = new LoadingState;
    loadingState->setLoadingPackage("data/core.package");
    g_gameFSM.addState(loadingState);

    extern char g_entityName[];
    extern char g_levelName[];

    switch(cfg.m_mode)
    {
    case 0:
        {
            TestGameState* pState = new TestGameState();
            g_gameFSM.addState(pState);
            loadingState->setLoadingFinishState(pState->m_nameId);
            break;
        }
    case 1:
        {
            RemoteViewerState* pState = new RemoteViewerState();
            g_gameFSM.addState(pState);
            loadingState->setLoadingFinishState(pState->m_nameId);
            if(loadEntityName) strcpy(g_entityName, loadEntityName);
            if(loadLevelName) strcpy(g_levelName, loadLevelName);
            break;
        }
    case 2:
        {
            RenderViewerState* pState = new RenderViewerState();
            g_gameFSM.addState(pState);
            loadingState->setLoadingFinishState(pState->m_nameId);
            break;
        }
    default:
        break;    
    }

    g_gameFSM.changeState(StringId(loadingState->getName()));
    g_engine.run();
    quitWebServerTool();
    g_engine.quit();
	return 0;
}

//===========================================================
static  char                                    g_frameBuf[1024*1024*5];//5M Frame Mem
static LinearAllocator  g_frameAllocator("frame-memory", g_frameBuf, sizeof(g_frameBuf));
static  char                                    g_staticBuf[1024*1024*3];//3M Static Mem
static LinearAllocator  g_staticAllocator("static-memory", g_staticBuf, sizeof(g_staticBuf));
#ifndef _RETAIL
static  char                                    g_debugBuf[1024*1024*2];
static LinearAllocator  g_debugAllocator("debug-memory", g_debugBuf, sizeof(g_debugBuf));
#endif
static MallocAllocator  g_havokAllocator("havok-memory");

void registerMemoryAllocators()
{
    g_memoryMgr.registerAllocator(kMemoryCategoryFrame, &g_frameAllocator);
    g_memoryMgr.registerAllocator(kMemoryCategoryStatic, &g_staticAllocator);
    g_memoryMgr.registerAllocator(kMemoryCategoryHavok, &g_havokAllocator);
#ifndef _RETAIL
    g_memoryMgr.registerAllocator(kMemoryCategoryDebug, &g_debugAllocator);
#endif
}
