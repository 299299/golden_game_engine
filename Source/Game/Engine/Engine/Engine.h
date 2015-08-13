#pragma once
#include "BaseTypes.h"

struct EngineConfig
{
    void*                       m_windowHandle;
    const char*                 m_windowTitle;
    int                         m_windowPosSize[4];
    int                         m_fixedFPS;
    bool                        m_fullScreen;
    bool                        m_headless;
};

struct GameConfig
{
    int                         m_max_rigs;
    int                         m_max_anim_evts;
    int                         m_max_anim_fsm;
    int                         m_max_characters;
    int                         m_max_geometries;
    int                         m_max_props;
    int                         m_max_physics_objects;
    int                         m_max_proxy_objects;
    int                         m_max_models;
    int                         m_max_lights;
    int                         m_max_raycast_per_frame;
    int                         m_debug_memory_size;
    int                         m_frame_memory_size;
    int                         m_havok_monitor_memory_size;
    int                         m_havok_frame_memory_size;
    bool                        m_havok_check_memory;
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
    // must run first !!!
    bool load_game_cfg(const char* cfg_file);

    void init(const EngineConfig& cfg);
    void quit();
    void run();

    void frame(float timeStep);
    bool running() const { return m_running;};
    void shutdown() { m_running = false;};

    void core_init();
    void subsystem_init();
    void core_shutdown();
    void subsystem_shutdown();

    EngineConfig                            m_cfg;
    GameConfig                              m_game_cfg;

    int                                     m_state;
    bool                                    m_running;
    char                                    m_padding[3];
};

void register_engine_factories();

extern Engine g_engine;
