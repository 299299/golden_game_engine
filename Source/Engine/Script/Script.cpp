#include "Script.h"
#include "Log.h"
#include "id_array.h"
#include "config.h"
#include "EngineAssert.h"
#include "Resource.h"
#include "Profiler.h"
#include <Windows.h>
#include <gamemonkey/gmThread.h>
#include <gamemonkey/gmStreamBuffer.h>
#include <gamemonkey/gmCall.h>

#define GC_TIME (2.0f)

static IdArray<MAX_SCRIPT_OBJECT, ScriptInstance> g_scriptObjects;

void* load_resource_script(const char* data, uint32_t size)
{
    ScriptResource* script = (ScriptResource*)data;
    script->m_code = (char*)data + sizeof(ScriptResource);
    return script;
}

void bringin_resource_script(void* resource)
{
    ScriptResource* script = (ScriptResource*)resource;
    script->pre_load();
}

void bringout_resource_script(void* resource)
{
    ScriptResource* script = (ScriptResource*)resource;
}

void ScriptResource::pre_load()
{
    if(m_preLoaded) return;
    gmStreamBufferStatic stream(m_code, m_codeSize);
    m_rootFunction = g_script.m_vm->BindLibToFunction(stream);
    g_script.m_vm->ExecuteFunction(m_rootFunction, 0, true);
    g_script.print_error();
    m_preLoaded = true;
}

void ScriptInstance::init( const void* resource)
{
    m_resource = (const ScriptResource*)resource;
    gmVariable a_param((int)m_actor);
    gmCall call;
    call.BeginGlobalFunction(g_script.m_vm, m_resource->m_funcName);
    call.AddParam(a_param);
    call.End(&m_threadId);
    m_table = call.GetReturnedVariable().GetTableObjectSafe();
    m_threadId = call_function("start");
}

void ScriptInstance::destroy()
{
    if(m_threadId < 0 || !m_table) return;
    call_function("stop");
    g_script.m_vm->KillThread(m_threadId);
    m_threadId = -1;
}

int ScriptInstance::call_function( const char* a_func_name, const gmVariable* a_param )
{
    gmCall call;
    call.BeginTableFunction(g_script.m_vm, a_func_name, m_table, gmVariable(m_table));
    if(a_param) call.AddParam(*a_param);
    int nThreadId = -1;
    call.End(&nThreadId);
    g_script.print_error();
    return nThreadId;
}

static bool GM_CDECL machine_callback(gmMachine * a_machine, gmMachineCommand a_command, const void * a_context)
{
    if(a_command == MC_THREAD_EXCEPTION)
    {
        LOGE("[GM] Execption!");
    }
    return true;
}
static void GM_CDECL print_callback(gmMachine * a_machine, const char * a_string)
{
    LOGI("[GameMonkey] %s.", a_string);
    OutputDebugString(a_string);
    OutputDebugString("\n");
}

ScriptSystem g_script;
void ScriptSystem::init()
{
    memset(this, 0x00, sizeof(ScriptSystem));
    m_vm = new gmMachine();
#ifndef _RETIAL
    m_vm->SetDebugMode(true);
#endif    
    gmMachine::s_machineCallback = machine_callback;
    gmMachine::s_printCallback = print_callback;
    extern void register_script_api(gmMachine*);
    extern void gmBindMathLib(gmMachine*);
    extern void gmBindStringLib(gmMachine*);
    register_script_api(m_vm);
    gmBindMathLib(m_vm);
    gmBindStringLib(m_vm);
    print_error();

    extern void register_debug_gui_api(gmMachine*);
    register_debug_gui_api(m_vm);
}

void ScriptSystem::quit()
{
    delete m_vm;
}

char script_error_buffer[1024*4];
void ScriptSystem::print_error()
{
    bool firstErr = true;
    gmLog & compileLog = m_vm->GetLog();
    const char *msg = compileLog.GetEntry(firstErr);
    if(!msg) return;

    memset(script_error_buffer, 0x00, sizeof(script_error_buffer));
    while(msg)	
    {
        LOGE(msg);
        strcat_s(script_error_buffer, msg);
        msg = compileLog.GetEntry(firstErr);
    }
    compileLog.Reset();
    msg_box(script_error_buffer, "[Script Error]");
}

int ScriptSystem::call_function(const char* a_obj_name, const char * a_func_name, gmVariable *a_param)
{
    int nThreadId = -1;
    gmTableObject* table = m_vm->GetGlobals()->Get(m_vm, a_obj_name).GetTableObjectSafe();
    if(!table) {
        LOGE("not find table %s", a_obj_name);
        return nThreadId;
    }
    gmCall call;
    call.BeginTableFunction(m_vm, a_func_name, table, gmVariable(table));
    if ( a_param ) call.AddParam( *a_param );
    call.End(&nThreadId);
    print_error();
    return nThreadId;
}

int ScriptSystem::call_global_function(const char* a_func_name, gmVariable* a_param)
{
    int nThreadId = -1;
    gmCall call;
    call.BeginGlobalFunction(m_vm, a_func_name);
    if(a_param) call.AddParam(*a_param);
    call.End(&nThreadId);
    print_error();
    return nThreadId;
}

void ScriptSystem::step(float dt)
{
    PROFILE(script_update);
    int nThreadCount = m_vm->Execute((gmint)(dt*1000));
    print_error();
}

void ScriptSystem::frame_end(float dt)
{
    m_time += dt;
    if(m_time < GC_TIME) return;
    m_time -= GC_TIME;
    m_vm->CollectGarbage();
}

void ScriptSystem::full_garbge_collect()
{
    m_vm->CollectGarbage(true);
}

//-----------------------------------------------------------------------
Id create_script_object(const void* resource, ActorId32 actor)
{
    if(!resource) 
    {
        Id id;
        id.id = INVALID_ID;
        return id;
    }
    ScriptInstance inst;
    inst.m_actor = actor;
    inst.init((const ScriptResource*)resource);
    return id_array::create(g_scriptObjects, inst);;
}
void destroy_script_object(Id id)
{
    if(!id_array::has(g_scriptObjects, id)) return;
    id_array::get(g_scriptObjects, id).destroy();
    id_array::destroy(g_scriptObjects, id);
}
void* get_script_object(Id id)
{
    if(!id_array::has(g_scriptObjects, id)) return 0;
    return &id_array::get(g_scriptObjects, id);
}
uint32_t num_script_objects()
{
    return id_array::size(g_scriptObjects);
}
void* get_script_objects()
{
    return id_array::begin(g_scriptObjects);
}
//-----------------------------------------------------------------------


