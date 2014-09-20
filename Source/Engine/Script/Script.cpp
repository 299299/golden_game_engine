#include "Script.h"
#include "Log.h"
#include "id_array.h"
#include "config.h"
#include <gamemonkey/gmThread.h>
#include <gamemonkey/gmStreamBuffer.h>

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
    gmStreamBufferStatic stream(script->m_code, script->m_codeSize);
    script->m_rootFunction = g_script.m_vm->BindLibToFunction(stream);
    if(!script->m_rootFunction) g_script.printError();
}

void bringout_resource_script(void* resource)
{
    ScriptResource* script = (ScriptResource*)resource;
    //script->m_rootFunction->Destruct(g_script.m_vm);
}


void ScriptInstance::init( const void* resource )
{
    m_resource = (const ScriptResource*)resource;
    bool bOK = g_script.m_vm->ExecuteFunction(m_resource->m_rootFunction, &m_threadId, true);

}

ScriptSystem g_script;
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
}

void ScriptSystem::init()
{
    m_vm = new gmMachine();
    m_vm->SetDebugMode(true);
    gmMachine::s_machineCallback = machine_callback;
    gmMachine::s_printCallback = print_callback;
}

void ScriptSystem::quit()
{
    delete m_vm;
}

void ScriptSystem::printError()
{
    bool firstErr = true;

    gmLog & compileLog = m_vm->GetLog();
    const char *msg = compileLog.GetEntry(firstErr);

    if ( msg )
    {
        LOGE("#############################\n[GameMonkey Run-time Error]:");
    }

    while(msg)	
    {
        LOGE(msg);
        msg = compileLog.GetEntry(firstErr);
    }

    compileLog.Reset();
}

void ScriptSystem::update()
{
    m_vm->Execute(16);
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