#include "ScriptSystem.h"
#include "Log.h"
#include <gamemonkey/gmThread.h>

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

void ScriptSystem::handleErrors()
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
