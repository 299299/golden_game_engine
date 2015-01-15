#include "GameState.h"
#include "Log.h"
#include "Profiler.h"
#include "Prerequisites.h"

GameState::GameState()
{

}

GameState::~GameState()
{

}

void GameState::pre_step( float dt )
{

}

void GameState::step( float dt )
{

}

void GameState::post_step( float dt )
{

}

void GameState::render()
{

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