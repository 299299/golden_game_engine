#include <gamemonkey/gmThread.h>
#include "Engine.h"
#include "Win32Context.h"
#include "XBoxInput.h"

struct gmVariableEntry
{
    const char* m_name;
    gmVariable  m_value;
};

static int GM_CDECL script_shutdown_game(gmThread* a_thread)
{
    g_engine.shutdown();
    return GM_OK;
}

static int GM_CDECL input_is_key_down(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(key_code, 0);
    a_thread->PushInt(g_win32Context.m_keyStatus[key_code]);
    return GM_OK;
}

void register_script_api(gmMachine* machine)
{
    machine->RegisterLibraryFunction("shut_down", script_shutdown_game);

    static gmFunctionEntry s_script_binding[] =  
    {
        {"is_key_down", input_is_key_down },
    };
    machine->RegisterLibrary(s_script_binding, sizeof(s_script_binding) / sizeof(gmFunctionEntry), "input");
    static gmVariableEntry s_input_values[] =
    {
        {"ESC", gmVariable(VK_ESCAPE)},
    };
    gmVariable va = machine->GetGlobals()->Get(machine, "input");
    gmTableObject* table = va.GetTableObjectSafe();
    for(size_t i = 0; i < sizeof(s_input_values) / sizeof(gmVariableEntry); ++i)
        table->Set(machine, s_input_values[i].m_name, s_input_values[i].m_value);
}