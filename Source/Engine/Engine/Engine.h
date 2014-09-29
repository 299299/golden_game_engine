#pragma once
#include "BaseTypes.h"

struct EngineConfig
{
    void*                       m_windowHandle;
    const char*                 m_windowTitle;
    int                         m_windowWidth;
    int                         m_windowHeight;
    int                         m_fixedFPS;
    bool                        m_fullScreen;
    bool                        m_checkMemory;
    bool                        m_headless;
};

enum EngineFrameState
{
    kFrameStart,
    kFramePreStepping,
    kFrameUpdating,
    kFramePostStepping,
    kFrameEnd,
    kFrameRendering,
    kFrameInvalid
};


struct Engine
{
    void init(const EngineConfig& cfg);
    void quit();
    void run();
    
    void frame(float timeStep);
    bool running() const { return m_running;};
    void shutdown() { m_running = false;};
    bool updating() const { return m_updating; };
    void set_update(bool bUpdate) { m_updating = bUpdate; };

    void apply_framelimit(double timeMS);
    void core_init();
    void subsystem_init();
    void core_shutdown();
    void subsystem_shutdown();

    EngineConfig                            m_cfg;
    int                                     m_state;
    bool                                    m_running;
    bool                                    m_updating;
};


extern Engine g_engine;
