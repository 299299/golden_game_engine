#pragma once
#include "BaseTypes.h"
#include "StringId.h"


ENGINE_NATIVE_ALIGN struct ScriptResource
{
    DECLARE_RESOURCE(script);
    const char* m_code;
};


struct ScriptInstance
{
    void init(const void* resource);
    const ScriptResource*       m_resource;
};

class gmMachine;
struct ScriptSystem
{
    void init();
    void quit();

    gmMachine*              m_vm;
    int                     m_threadId;

private:
    void handleErrors();
};

extern ScriptSystem g_script;