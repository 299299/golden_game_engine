#include "GameState.h"
#include "Log.h"
#include "Profiler.h"
#include "Actor.h"
#include "Win32Context.h"
#include "RenderCamera.h"
#include "DebugDraw.h"
#include "Engine.h"


static void swith_graphics_debug( uint32_t flag )
{
    static int _bgfx_debug = BGFX_DEBUG_TEXT;
    if(!HAS_BITS(_bgfx_debug,flag))
        ADD_BITS(_bgfx_debug, flag);
    else
        REMOVE_BITS(_bgfx_debug, flag);
    bgfx::setDebug(_bgfx_debug);
}

GameState::GameState()
{

}

GameState::~GameState()
{

}

void GameState::pre_step( float dt )
{
    g_actorWorld.pre_step(dt);
}

void GameState::step( float dt )
{
    g_actorWorld.step(dt);
}

void GameState::post_step( float dt )
{
    g_actorWorld.post_step(dt);
}

void GameState::render()
{
    g_actorWorld.draw();
}

void GameState::step_debug_ctrl(float dt)
{
    static bool _show_profile = false;
    static bool _draw_debug_graphics = false;

    if(g_win32Context.is_key_just_pressed(VK_F1))
        _show_profile = !_show_profile;
    else if(g_win32Context.is_key_just_pressed(VK_F2))
        _draw_debug_graphics = !_draw_debug_graphics;
    else if(g_win32Context.is_key_just_pressed(VK_F3))
        swith_graphics_debug(BGFX_DEBUG_WIREFRAME);
    else if(g_win32Context.is_key_just_pressed(VK_F4))
        swith_graphics_debug(BGFX_DEBUG_STATS);

    if(g_win32Context.is_key_just_pressed(VK_ESCAPE))
        g_engine.shutdown();

    if(g_win32Context.is_key_just_pressed(VK_SPACE))
    {
        static int index = 0;
        static float scales[] = {0.125f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f};
        if(index >= BX_COUNTOF(scales))
            index = 0;
        extern float g_timeScale;
        g_timeScale = scales[index];
        LOGD("change time scale to %f!!!", g_timeScale);
        ++index;
    }

    if(_show_profile)
        g_profiler.dump();

    if(_draw_debug_graphics)
    {
        extern void debug_draw_models();
        extern void debug_draw_lights();
        extern void debug_draw_animation(float);
        debug_draw_lights();
        debug_draw_models();
        debug_draw_animation(dt);
    }

    extern void resource_hot_reload_update(float);
    resource_hot_reload_update(dt);

    debug_update_vdb_camera();
}

GameFSM g_gameFSM;

GameFSM::GameFSM()
:m_state(0)
,m_numStates(0)
{
    memset(m_states, 0x00, sizeof(m_states));
}

GameFSM::~GameFSM()
{

}

void GameFSM::init()
{
    for(int i=0; i<m_numStates; ++i)
    {
        m_states[i]->init();
    }
}

void GameFSM::quit()
{
    for(int i=0; i<m_numStates; ++i)
    {
        delete m_states[i];
    }
}

void GameFSM::add_state(GameState* p_state)
{
    ENGINE_ASSERT(m_numStates + 1 < MAX_GAME_STATES, "game state num overflow.");
    m_states[m_numStates++] = p_state;
}

void GameFSM::change_state(const char* name)
{
    change_state(find_state(name));
}

void GameFSM::change_state( GameState* state )
{
    GameState* cur_state = m_state;
    GameState* next_state = state;
    if(cur_state == next_state) return;
    if(!next_state) return;
    LOGI("change_state from %s to %s.", cur_state ? cur_state->get_name() : "(null)",  next_state->get_name());
    if(cur_state) cur_state->on_exit(next_state);
    next_state->on_enter(cur_state);
    m_state = next_state;
}

GameState* GameFSM::find_state(const char* name)
{
    int num = m_numStates;
    GameState** states = m_states;
    for(int i=0; i<num; ++i)
    {
        GameState* state = states[i];
        if(!strcmp(state->get_name(), name))
            return state;
    }
    return 0;
}

void GameFSM::pre_step(float dt)
{
    if(!m_state) return;
    m_state->pre_step(dt);
}

void GameFSM::step(float dt)
{
    if(!m_state) return;
    m_state->step(dt);
}

void GameFSM::post_step(float dt)
{
    if(!m_state) return;
    m_state->post_step(dt);
}

void GameFSM::render()
{
    if(!m_state) return;
    m_state->render();
}