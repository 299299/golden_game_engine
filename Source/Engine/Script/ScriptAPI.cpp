#include "Engine.h"
#include "Win32Context.h"
#include "XBoxInput.h"
#include "Resource.h"
#include "EngineAssert.h"
#include <bx/bx.h>
#include <gamemonkey/gmThread.h>

#ifdef GetObject
#undef GetObject
#endif

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
static int GM_CDECL string_to_id(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(str, 0);
    a_thread->PushInt(StringId::calculate(str));
    return GM_OK;
}
#ifndef _RETAIL
static int GM_CDECL id_to_string(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(id, 0);
    a_thread->PushNewString(stringid_lookup(StringId(id)));
    return GM_OK;
}
#endif

static int GM_CDECL input_is_key_down(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(key_code, 0);
    a_thread->PushInt(g_win32Context.m_keyStatus[key_code]);
    return GM_OK;
}

//-------------------------------------------------------------------------
// RESOURCE
static int GM_CDECL resource_package_load(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(pack_name, 0);
    g_resourceMgr.loadPackage(pack_name);
    return GM_OK;
}

static int GM_CDECL resource_package_load_and_wait(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(pack_name, 0);
    g_resourceMgr.loadPackageAndWait(pack_name);
    return GM_OK;
}

static int GM_CDECL resource_package_unload(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(pack_name, 0);
    g_resourceMgr.unloadPackage(StringId(pack_name));
    return GM_OK;
}

static int GM_CDECL resource_package_get_status(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(pack_name, 0);
    a_thread->PushInt(g_resourceMgr.getPackageStatus(StringId(pack_name)));
    return GM_OK;
}

static int GM_CDECL resource_package_flush(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(pack_name, 0);
    GM_CHECK_INT_PARAM(max_num, 1);
    g_resourceMgr.flushPackage(StringId(pack_name), max_num);
    return GM_OK;
}
//-------------------------------------------------------------------------

void register_enum_values(gmMachine* machine, const char* libName, gmVariableEntry* entries, uint32_t numEntries)
{
    gmVariable va = machine->GetGlobals()->Get(machine, libName);
    gmTableObject* table = va.GetTableObjectSafe();
    ENGINE_ASSERT(table, "can not find script table %s", libName);
    for(size_t i = 0; i < numEntries; ++i)
        table->Set(machine, entries[i].m_name, entries[i].m_value);
}

void register_script_api(gmMachine* machine)
{
    static gmFunctionEntry s_core_binding[] =  
    {
        {"shut_down", script_shutdown_game },
        {"string_to_id", string_to_id},
#ifndef _RETAIL
        {"id_to_string", id_to_string},
#endif
    };
    machine->RegisterLibrary(s_core_binding, BX_COUNTOF(s_core_binding), 0, false);

    static gmFunctionEntry s_resource_binding[] =
    {
        {"get_package_status", resource_package_get_status},
        {"load_package", resource_package_load,},
        {"load_package_and_wait", resource_package_load_and_wait},
        {"unload_package", resource_package_unload},
        {"flush_package", resource_package_flush},
    };
    static gmVariableEntry s_resource_values[] =
    {
        {"LOADING", gmVariable(kResourceLoading)},
        {"OFFLINE", gmVariable(kResourceOffline)},
        {"ONLINE", gmVariable(kResourceOnline)},
        {"ERROR", gmVariable(kResourceError)},
        {"UNLOADING", gmVariable(kResourceRequestUnload)},
    };
    machine->RegisterLibrary(s_resource_binding, BX_COUNTOF(s_resource_binding), "resource");
    register_enum_values(machine, "resource", s_resource_values, BX_COUNTOF(s_resource_values));

    static gmFunctionEntry s_script_binding[] =  
    {
        {"is_key_down", input_is_key_down },
    };
    machine->RegisterLibrary(s_script_binding, BX_COUNTOF(s_script_binding), "input");
    static gmVariableEntry s_input_values[] =
    {
        {"ESC", gmVariable(VK_ESCAPE)},
        {"ENTER", gmVariable(VK_RETURN)},
        {"SPACE", gmVariable(VK_SPACE)},
        {"F1", gmVariable(VK_F1)},
        {"F2", gmVariable(VK_F2)},
        {"F3", gmVariable(VK_F3)},
        {"F4", gmVariable(VK_F4)},
        {"F5", gmVariable(VK_F5)},
        {"F6", gmVariable(VK_F6)},
        {"F7", gmVariable(VK_F7)},
        {"F8", gmVariable(VK_F8)},
        {"F9", gmVariable(VK_F9)},
        {"F10", gmVariable(VK_F10)},
        {"F11", gmVariable(VK_F11)},
        {"F12", gmVariable(VK_F12)},
    };
    register_enum_values(machine, "input", s_input_values, BX_COUNTOF(s_input_values));
}