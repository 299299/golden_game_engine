#pragma once
#include "BaseTypes.h"
#include "StringId.h"

class gmFunctionObject;
class gmMachine;
struct gmVariable;
class gmTableObject;
class gmFunctionObject;

ENGINE_NATIVE_ALIGN struct ScriptResource
{
    DECLARE_RESOURCE(script);
    const char*             m_code;
    uint32_t                m_codeSize;
    gmFunctionObject*       m_rootFunction;
};


struct ScriptInstance
{
    void init(const void* resource);
    void destroy();

    const ScriptResource*       m_resource;
    int                         m_threadId;
};


struct ScriptSystem
{
    void init();
    void quit();

    void print_error();
    void call_function(const char* a_obj_name, const char * a_func_name, gmVariable *a_param);
    void call_global_function(const char* a_func_name, gmVariable* a_param);

    void pre_step(float dt);
    void update(float dt);
    void post_step(float dt);
    void render();
    void ready();

    gmMachine*              m_vm;
    int                     m_threadId;
    float                   m_time;

    gmTableObject*          m_core_table;
    gmFunctionObject*       m_pre_step_func;
    gmFunctionObject*       m_post_step_func;
    gmFunctionObject*       m_update_func;
    gmFunctionObject*       m_render_func;
};

extern ScriptSystem g_script;