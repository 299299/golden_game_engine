#include "Engine.h"
#include "Log.h"
#include "WebServerTool.h"
#include "MemorySystem.h"
#include "Utils.h"
#include "linear_allocator.h"
#include "Script.h"
#include "Resource.h"
#include "DebugDraw.h"
#include "Graphics.h"
#include "Script.h"
#include "Utils.h"
//==================================================
#include <Windows.h>
#include <tchar.h>
#include <bx/bx.h>
#include <bx/commandline.h>

void showHelp()
{
    printf("Usage: Game [options]\n"
            "Options:\n"
            "-m set game mode(0-test, 1-remote, 2-render)\n"
            "-w set window width\n"
            "-h set window height\n"
            "--actor previewer --> actor name\n"
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
    name = cmdline.findOption("actor");
    if(name) loadEntityName = name;
    name = cmdline.findOption("level");
    if(name) loadLevelName = name;
    if(cmdline.hasArg("debug")) msg_box("wait for visual studio attach process.", "ENGINE");

    if(cfg.m_mode == 1)
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

    static const char* window_names[] =
    {
        "test-game", "remote-viewer", "render-viewer",
    };
    cfg.m_webServer = cfg.m_mode == 1;
    cfg.m_windowTitle = window_names[cfg.m_mode];

    extern void register_memory_allocators();
    register_memory_allocators();

    g_engine.init(cfg);

    extern void resource_hot_reload_init();
    resource_hot_reload_init();

    extern char g_actorName[];
    extern char g_levelName[];

    if(loadEntityName) strcpy(g_actorName, loadEntityName);
    if(loadLevelName) strcpy(g_levelName, loadLevelName);

    g_resourceMgr.load_package_and_wait("data/core.package");

    Graphics::ready();
    g_debugDrawMgr.ready();
    g_script.ready();
    
    g_engine.run();
    quitWebServerTool();
    g_engine.quit();
	return 0;
}

//===========================================================
static char             g_frameBuf[1024*1024*5];//5M Frame Mem
static LinearAllocator  g_frameAllocator(g_frameBuf, sizeof(g_frameBuf));

void register_memory_allocators()
{
    g_memoryMgr.register_allocator(kMemoryCategoryFrame, &g_frameAllocator);
}
