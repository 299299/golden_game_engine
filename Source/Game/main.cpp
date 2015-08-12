#include "Prerequisites.h"
#include "Utils.h"
#include "DataDef.h"
#include "Profiler.h"
#include <iostream>
#include <bx/commandline.h>

void showHelp()
{
    printf("Usage: Game --action [action] [options]\n"
        "Game actions:\n"
        "-----------------------------------------\n"
        "Game, HavokConvert, DataCompile \n"
        "-----------------------------------------\n"
        "Common options:\n"
        "--debug wait for debug attach when launched.\n"
        "-----------------------------------------\n"
        "Game options:\n"
        "-w set window width\n"
        "-h set window height\n"
        "-t set window title\n"
        "--package --> package to load\n"
        "--state --> game state to run\n"
        "--actor --> actor name\n"
        "--level --> level name\n"
        "--animation --> animation name\n"
        "--headless no graphics & no window\n"
        "--autoreload auto reload resource if file is changed \n"
        "--compile will data compile first than run the game \n"
        "-----------------------------------------\n"
        "Havok Converter options\n"
        "-m specific convert mode(model, skin, animation, level)\n"
        "-f specific input hkx file\n"
        "-o specific output folder\n"
        "--slient do not show error msg box\n"
        "--packnormal pack normal\n"
        "--packuv pack uv\n"
        "--verpose pack uv\n"
        "-b to force not merge old json\n"
        "-----------------------------------------\n"
        "Data Compiler options\n"
        "-i input dir \n"
        "-o output folder\n"
        "-m compile mode default 0\n"
        "-t set num of threads to compile\n"
        "-b to force recompile\n"
        "--bundle bundle all resource to package file\n"
        "--slient do not show error msg box\n"
        "--ignore_texture to ignore converting all dds \n");
}

typedef int (*func_app_main)(int, bx::CommandLine*);
extern int havok_convert_main(int, bx::CommandLine*);
extern int data_compiler_main(int, bx::CommandLine*);
extern int game_main(int, bx::CommandLine*);

struct game_app
{
    const char*     name;
    func_app_main   func;
};
game_app g_apps[] =
{
    { "HavokConvert", havok_convert_main },
    { "DataCompile", data_compiler_main },
    { "Game", game_main },
};

int main(int argc, char* argv[])
{
    showHelp();

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
    // Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
    // Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

    bx::CommandLine cmdline(argc, argv);
    const char* action = cmdline.findOption("action");
    if(cmdline.hasArg("debug"))
    {
        msg_box("wait for visual studio attach process.");
    }

    if(!action)
        return kErrorAction;

    int num = BX_COUNTOF(g_apps);
    game_app* app = NULL;
    for (int i=0; i<num; ++i)
    {
        if(!strcmp(g_apps[i].name, action))
        {
            app = &g_apps[i];
            break;
        }
    }

    HiresTimer::init();
    return app ? app->func(argc, &cmdline) : kErrorAction;
}