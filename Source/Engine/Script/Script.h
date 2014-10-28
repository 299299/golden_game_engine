#pragma once
#include "BaseTypes.h"
#include "StringId.h"
#include "Utils.h"

class gmFunctionObject;
class gmMachine;
struct gmVariable;
class gmTableObject;
class gmFunctionObject;
struct ScriptResource;

struct ScriptInclude
{
    StringId                m_name;
    ScriptResource*         m_script;
};

#define SCRIPT_FUNCTION_MAX_LEN     32

ENGINE_NATIVE_ALIGN struct ScriptResource
{
    DECLARE_RESOURCE(script);

    const char*             m_code;
    uint32_t                m_codeSize;
    gmFunctionObject*       m_rootFunction;
    bool                    m_preLoaded;
    char                    m_padding[3];
    char                    m_funcName[SCRIPT_FUNCTION_MAX_LEN];                  

    void pre_load();
};

ENGINE_NATIVE_ALIGN struct ScriptInstance
{
    void init(const void* resource);
    void destroy();
    int  call_function(const char* a_func_name, const gmVariable* a_param = 0);

    const ScriptResource*       m_resource;
    gmTableObject*              m_table;
    int                         m_threadId;
    ActorId32                   m_actor;
};


struct ScriptSystem
{
    void init();
    void quit();
    void step(float dt);

    void print_error();
    int  call_function(const char* a_obj_name, const char * a_func_name, gmVariable *a_param);
    int  call_global_function(const char* a_func_name, gmVariable* a_param);
    void frame_end(float dt);
    void full_garbge_collect();

    gmMachine*              m_vm;
    float                   m_time;
    ScriptInstance*         m_coreScript;
};

extern ScriptSystem g_script;