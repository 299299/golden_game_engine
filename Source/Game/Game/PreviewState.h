#pragma once
#include "GameState.h"
#include "BaseTypes.h"
#include "GameConfig.h"
#include "StringId.h"

struct Level;
struct Actor;
struct ActorResource;
struct ComponentData;

typedef void (*func_debugdraw_component_imgui_t)(void*, ComponentData*);

struct ComponentDebugDrawGUI
{
    StringId                m_name;
    func_debugdraw_component_imgui_t    m_function;
};

class PreviewState : public GameState
{
public:
    PreviewState();
    ~PreviewState();

    virtual const char* get_name() const { return "preview"; };
    virtual void step(float dt);
    virtual void on_enter(GameState* prev_state);
    virtual void process_cmd_args(void*);

    void swith_graphics_debug(uint32_t flag);
    void draw_actor_info(const char* name, ActorId32 _actorId, int _x, int _y, int _w, int _h);
    ComponentDebugDrawGUI* find_component_gui(StringId _type);
    void draw_level_info(const char* name, Level* level, int _x, int _y, int _w, int _h);
    void draw_components_info(ActorId32 actorId);

    ActorId32                   m_preview_actor;
    Level*                      m_preview_level;

    const char*                 m_actor_name;
    const char*                 m_level_name;

    uint32_t                    m_bgfx_debug;
    bool                        m_show_profile;
    bool                        m_draw_debug_graphics;
    
    int                         m_num_component_gui;
    ComponentDebugDrawGUI       m_component_gui[MAX_COMPONENT_TYPES];
};

