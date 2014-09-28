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
    script->m_code = (char*)data + script->m_codeOffset;
    script->m_includes = (ScriptInclude*)((char*)data + sizeof(ScriptResource));
    return script;
}

void lookup_resource_script(void* resource)
{
    ScriptResource* script = (ScriptResource*)resource;
    for (uint32_t i = 0; i < script->m_numIncs; ++i)
    {
        script->m_includes[i].m_script = FIND_RESOURCE(ScriptResource, script->m_includes[i].m_name);
    }
}

void bringin_resource_script(void* resource)
{
    ScriptResource* script = (ScriptResource*)resource;
    for (uint32_t i = 0; i < script->m_numIncs; ++i)
    {
        script->m_includes[i].m_script->pre_load();
    }
    script->pre_load();
}

void bringout_resource_script(void* resource)
{
    ScriptResource* script = (ScriptResource*)resource;
    if(script->m_threadId < 0) return;
    g_script.m_vm->KillThread(script->m_threadId);
    script->m_threadId = -1;
}

int ScriptResource::execute() const
{
    int nThreadId = -1;
    g_script.m_vm->ExecuteFunction(m_rootFunction, &nThreadId, true);
    g_script.print_error();
    return nThreadId;
}

void ScriptResource::pre_load()
{
    if(m_threadId > 0) return;
    gmStreamBufferStatic stream(m_code, m_codeSize);
    m_rootFunction = g_script.m_vm->BindLibToFunction(stream);
    g_script.print_error();
    m_threadId = execute();
    gmThread* p_thread = g_script.m_vm->GetThread(m_threadId);
    if(!p_thread) m_threadId = -1;
}

void ScriptInstance::init( const void* resource )
{
    m_resource = (const ScriptResource*)resource;
    m_threadId = m_resource->execute();
}

void ScriptInstance::destroy()
{
    if(m_threadId < 0) return;
    g_script.m_vm->KillThread(m_threadId);
    m_threadId = -1;
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
    LOGI("[GM] print %s.", a_string);
    OutputDebugString(a_string);
    OutputDebugString("\n");
}

ScriptSystem g_script;
void ScriptSystem::init()
{
    memset(this, 0x00, sizeof(ScriptSystem));
    m_vm = new gmMachine();
    m_core_thread_id = -1;
    m_vm->SetDebugMode(true);
    gmMachine::s_machineCallback = machine_callback;
    gmMachine::s_printCallback = print_callback;
    extern void register_script_api(gmMachine*);
    extern void gmBindMathLib(gmMachine*);
    extern void gmBindStringLib(gmMachine*);
    extern void gmBindSystemLib(gmMachine*);
    register_script_api(m_vm);
    gmBindMathLib(m_vm);
    gmBindStringLib(m_vm);
    gmBindSystemLib(m_vm);
    print_error();
}

void ScriptSystem::quit()
{
    if(m_core_table) call_function("g_core", "shutdown", 0);
    delete m_vm;
}

void ScriptSystem::ready()
{
    if(m_core_thread_id >= 0)
    {
        m_vm->KillThread(m_core_thread_id);
        m_core_thread_id = -1;
    }
    m_core_script = FIND_RESOURCE(ScriptResource, StringId("core/scripts/core"));
    m_core_table = m_vm->GetGlobals()->Get(m_vm, "g_core").GetTableObjectSafe();
    ENGINE_ASSERT(m_core_table, "get g_core failed.");
    m_core_thread_id = call_function("g_core", "init", 0);
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
    
}

void ScriptSystem::pre_step( float dt )
{
    PROFILE(script_update);
    int nThreadCount = m_vm->Execute((gmint)(dt*1000));
    print_error();
}

void ScriptSystem::post_step( float dt )
{

}

void ScriptSystem::frame_end(float dt)
{
    m_time += dt;
    if(m_time < GC_TIME) return;
    m_time -= GC_TIME;
    m_vm->CollectGarbage();
}



//-----------------------------------------------------------------------
Id create_script_object(const void* resource)
{
    ScriptInstance inst;
    inst.init(resource);
    return id_array::create(g_scriptObjects, inst);
}
void destroy_script_object(Id id)
{
    if(!id_array::has(g_scriptObjects, id)) return;
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


