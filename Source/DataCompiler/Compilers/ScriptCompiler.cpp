#include "ScriptCompiler.h"
#include <gamemonkey/gmMachine.h>
#include <gamemonkey/gmStreamBuffer.h>
#include "Script.h"
#include "CommonUtils.h"

bool ScriptCompiler::process( const std::string& input, const std::string& output )
{
    char* buf = 0;
    if(!read_file(input, &buf)) return false;
    
    gmStreamBufferDynamic stream;
    int nErrors = g_script.m_vm->CompileStringToLib(buf, stream);
    if(nErrors > 0)
    {
        g_script.printError();
        return false;
    }

    uint32_t memSize = sizeof(ScriptResource) + stream.GetSize();
    char* mem = (char*)malloc(memSize);
    memset(mem, 0x00, memSize);
    ScriptResource* script = (ScriptResource*)mem;
    script->m_codeSize = stream.GetSize();
    char* p = mem;
    p += sizeof(ScriptResource);
    memcpy(p, stream.GetData(), stream.GetSize());
    bool bRet = write_file(output, mem, memSize);
    free(mem);
    return bRet;
}

