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
        scriptErr += msg;
        while(msg)	
        {
            msg = compileLog.GetEntry(firstErr);
            if(msg) scriptErr += msg;
        }
        compileLog.Reset();
        addError("Script %s compile err: %s", input.c_str(), scriptErr.c_str());
        return false;
    }

    const std::string include_keyword("//inc ");
    const uint32_t key_len = include_keyword.length();
    std::vector<std::string> include_files;
    char* head = buf;
    char* offset = strchr(head, '\n');
    while(offset)
    {
        uint32_t line_len = (uint32_t)(offset-head);
        std::string line(head, line_len);
        if(!str_begin_with(line, include_keyword))
            break;
        std::string include_file = std::string(head + key_len, line_len - key_len);
        include_files.push_back(include_file);
        head = offset + 1;
        offset = strchr(head, '\n');
    }

    uint32_t numOfIncludes = include_files.size();
    uint32_t memSize = sizeof(ScriptResource) + stream.GetSize() + sizeof(ScriptInclude) * numOfIncludes;
    char* mem = (char*)malloc(memSize);
    memset(mem, 0x00, memSize);
    ScriptResource* script = (ScriptResource*)mem;
    script->m_codeSize = stream.GetSize();
    script->m_threadId = -1;
    char* p = mem;
    p += sizeof(ScriptResource);
    ScriptInclude* includes = (ScriptInclude*)p;
    for (uint32_t i = 0; i < numOfIncludes; ++i)
    {
        ScriptInclude& include = includes[i];
        include.m_name = StringId(include_files[i].c_str());
        addDependency("include script", name_to_file_path(include_files[i], ScriptResource::get_name()));
    }
    p += sizeof(ScriptInclude) * numOfIncludes;
    script->m_codeOffset = (uint32_t)(p - mem);
    memcpy(p, stream.GetData(), stream.GetSize());
    bool bRet = write_file(output, mem, memSize);
    free(mem);
    free(buf);

    return bRet;
}

