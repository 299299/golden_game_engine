#pragma once
#include "BaseTypes.h"
#include "StringId.h"

class gmFunctionObject;
class gmMachine;

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
    const ScriptResource*       m_resource;
    int                         m_threadId;
};


struct ScriptSystem
{
    void init();
    void quit();
    void update();
    void printError();

    gmMachine*              m_vm;
    int                     m_threadId;
};

extern ScriptSystem g_script;