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

ENGINE_NATIVE_ALIGN struct ScriptResource
{
    DECLARE_RESOURCE(script);

    const char*             m_code;
    uint32_t                m_codeSize;
    gmFunctionObject*       m_rootFunction;
    bool                    m_preLoaded;
    char                    m_padding[3];

    void pre_load();
};


struct ScriptInstance
{
    void init(const void* resource, Id id);
    void destroy();
    void reload(const ScriptResource* resource);
    int  call_function(const char* a_func_name, const gmVariable* a_param = 0);

    const ScriptResource*       m_resource;
    gmTableObject*              m_table;
    int                         m_threadId;
};


struct ScriptSystem
{
    void init();
    void quit();

    void pre_step(float dt);
    void step(float dt);
    void post_step(float dt);

    void print_error();
    int  call_function(const char* a_obj_name, const char * a_func_name, gmVariable *a_param);
    int  call_global_function(const char* a_func_name, gmVariable* a_param);
    void frame_end(float dt);
    void full_garbge_collect();

    void ready();

    void add_key(const StringId& k, uint32_t type);

    gmMachine*              m_vm;
    float                   m_time;
    ScriptInstance*         m_coreScript;
};

extern ScriptSystem g_script;