#include "ScriptCompiler.h"
#include <gamemonkey/gmMachine.h>
#include <gamemonkey/gmStreamBuffer.h>
#include "Script.h"
#include "CommonUtils.h"

bool ScriptCompiler::process( const std::string& input, const std::string& output )
{
    char* buf = 0;
    uint32_t fileSize = read_file(input, &buf);
    if(!fileSize) return false;
    
    gmMachine* vm = g_script.m_vm;
    gmStreamBufferDynamic stream;
    int nErrors = vm->CompileStringToLib(buf, stream);
    if(nErrors > 0)
    {
        gmLog & compileLog = vm->GetLog();
        bool firstErr = true;
        std::string scriptErr;
        const char* msg = compileLog.GetEntry(firstErr);
        while(msg)	
        {
            scriptErr += msg;
            msg = compileLog.GetEntry(firstErr);
            if(msg) scriptErr += msg;
        }
        compileLog.Reset();
        addError("Script %s compile err: %s", input.c_str(), scriptErr.c_str());
        return false;
    }

    uint32_t memSize = sizeof(ScriptResource) + stream.GetSize();
    char* mem = (char*)malloc(memSize);
    memset(mem, 0x00, memSize);
    ScriptResource* script = (ScriptResource*)mem;
    std::string script_name = getFileName(input);
    script_name = "create_" + script_name;
    uint32_t name_len = script_name.length();
    ENGINE_ASSERT(name_len < SCRIPT_FUNCTION_MAX_LEN, "script function name %s overflow", script_name.c_str());
    strncpy(script->m_funcName, script_name.c_str(), name_len);
    script->m_codeSize = stream.GetSize();

    char* p = mem;
    p += sizeof(ScriptResource);
    memcpy(p, stream.GetData(), stream.GetSize());
    bool bRet = write_file(output, mem, memSize);
    free(mem);
    free(buf);

    return bRet;
}

