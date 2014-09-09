#pragma once

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