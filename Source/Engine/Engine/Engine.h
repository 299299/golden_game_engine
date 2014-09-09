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
    bool                        m_webServer;
    uint8_t                     m_mode;
    bool                        m_headless;
};


struct Engine
{
    void init(const EngineConfig& cfg);
    void quit();
    void run();
    
    void frame(float timeStep);
    bool isRunning() const { return m_running;};
    void shutdown() { m_running = false;};
    bool isUpdating() const { return m_updating; };
    void setUpdate(bool bUpdate) { m_updating = bUpdate; };

    void applyFrameLimit(double timeMS);
    void coreInit();
    void subSystemsInit();
    void coreShutdown();
    void subSystemsShutdown();

    EngineConfig                            m_cfg;
    bool                                    m_running;
    bool                                    m_updating;
};


extern Engine g_engine;
