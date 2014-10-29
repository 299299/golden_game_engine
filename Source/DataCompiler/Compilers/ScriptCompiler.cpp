#include "ScriptCompiler.h"
#include <gamemonkey/gmMachine.h>
#include <gamemonkey/gmStreamBuffer.h>
#include <gamemonkey/gmCall.h>
#include "Script.h"
#include "CommonUtils.h"

bool ScriptCompiler::process( const std::string& input, const std::string& output )
{
    FileReader scriptReader(input);
    if(!scriptReader.m_size) return false;
    
    gmMachine* vm = g_script.m_vm;
    gmStreamBufferDynamic stream;
    int nErrors = vm->CompileStringToLib(scriptReader.m_buf, stream);
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

    std::string script_name = getFileName(input);
    //just ignore the include script.
    if(!str_end_with(script_name, "include"))
    {
        script_name = "create_" + script_name;
        //check if this function name is exist or not.
        gmFunctionObject* rootFunction = vm->BindLibToFunction(stream);
        vm->ExecuteFunction(rootFunction, 0, true);
        gmFunctionObject* func = vm->GetGlobals()->Get(vm, script_name.c_str()).GetFunctionObjectSafe();
        if(!func)
        {
            addError("Script %s function name %s not found!", input.c_str(), script_name.c_str());
            return false;
        }
    }


#if 1
	//dump the functions of script table
	gmVariable a_param(0);
	gmCall call;
	call.BeginGlobalFunction(g_script.m_vm, script_name.c_str());
	call.AddParam(a_param);
	call.End();
	gmTableObject* table = call.GetReturnedVariable().GetTableObjectSafe();
	gmTableIterator iter;
	gmTableNode* child_node = table->GetFirst(iter);
	char buf[1024];
	while(child_node)
	{
		child_node->m_value.AsStringWithType(vm, buf, sizeof(buf));
		LOGI("script child key = %s", buf);
		child_node->m_key.AsStringWithType(vm, buf, sizeof(buf));
		LOGI("script child value = %s", buf);
		child_node = table->GetNext(iter);
	}
#endif

    uint32_t memSize = sizeof(ScriptResource) + stream.GetSize();
    MemoryBuffer mem(memSize);
    ScriptResource* script = (ScriptResource*)mem.m_buf;

    uint32_t name_len = script_name.length();
    ENGINE_ASSERT(name_len < SCRIPT_FUNCTION_MAX_LEN, "script function name %s overflow", script_name.c_str());
    strncpy(script->m_funcName, script_name.c_str(), name_len);
    script->m_codeSize = stream.GetSize();
    memcpy(mem.m_buf + sizeof(ScriptResource), stream.GetData(), stream.GetSize());
    return write_file(output, mem.m_buf, memSize);
}

bool ScriptCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    
    std::string script_file = JSON_GetString(root.GetValue("script_file"));
    if(script_file.empty())
    {
        LOGE("script ---> pack error.");
        return false;
    }

    LOGI("processing script_file %s", script_file.c_str());
    return process(script_file, m_output);
}