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
    ScriptInclude*          m_includes;
    uint32_t                m_numIncs;
    int                     m_threadId;
    uint32_t                m_codeOffset;

    int execute() const;
    void pre_load();
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
    void update(float dt);

    void print_error();
    void call_function(const char* a_obj_name, const char * a_func_name, gmVariable *a_param);
    void call_global_function(const char* a_func_name, gmVariable* a_param);
    void frame_end(float dt);

    void ready();

    void    add_key(const StringId& k, uint32_t type);
    bool    has_key(const StringId& k) const;
    uint32_t value_type(const StringId& k);
    bool    get_key(const StringId& k, int& v) const;
    bool    get_key(const StringId& k, float& v) const;
    bool    get_key(const StringId& k, StringId& v) const;
    bool    get_key(const StringId& k, float* v) const;
    bool    set_key(const StringId& k, int v);
    bool    set_key(const StringId& k, float v);
    bool    set_key(const StringId& k, const StringId& v);
    bool    set_key(const StringId& k, const float* v);

    gmMachine*              m_vm;
    int                     m_threadId;
    float                   m_time;

    gmTableObject*          m_core_table;
    //gmFunctionObject*       m_pre_step_func;

    Fact                    m_fact;
};

extern ScriptSystem g_script;