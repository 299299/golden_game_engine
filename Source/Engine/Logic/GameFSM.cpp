#include "GameFSM.h"
#include "GameState.h"
#include "Log.h"
#include <string.h>

GameFSM g_gameFSM;

void GameFSM::init()
{
    memset(this, 0x00, sizeof(GameFSM));
}

void GameFSM::quit()
{
    for(int i=0; i<m_numStates; ++i)
    {
        delete m_states[i];
    }
}

void GameFSM::frameStart(float timeStep)
{
    if(!m_curState)
        return;

    if(!m_curState->m_nextStateName.isZero())
        changeState(findState(m_curState->m_nextStateName));
    m_curState->frameStart(timeStep);
}

void GameFSM::frameEnd(float timeStep)
{
    if(!m_curState)
        return;

    m_curState->frameEnd(timeStep);
}

void GameFSM::render()
{
    if(!m_curState)
        return;

    m_curState->render();
}

void GameFSM::preStep(float timeStep)
{
    if(!m_curState)
        return;

    m_curState->preStep(timeStep);
}

void GameFSM::step(float timeStep)
{
    if(!m_curState)
        return;

    m_curState->step(timeStep);
}

void GameFSM::postStep(float timeStep)
{
    if(!m_curState)
        return;

    m_curState->postStep(timeStep);
}

GameState* GameFSM::findState(const StringId& name) const
{
    for(int i=0; i<m_numStates; ++i)
    {
        if(m_states[i]->m_nameId == name)
            return m_states[i];
    }
    return NULL;
}

void GameFSM::changeState(const StringId& name)
{
    changeState(findState(name));
}

void GameFSM::changeState(GameState* pState)
{
    if(m_curState == pState || !pState)
        return;

    const char* oldStateName = "null";
    if(m_curState) {
        oldStateName = m_curState->getName();
        m_curState->onExit(pState);
    }

    pState->m_timeInState = 0;
    pState->onEnter(m_curState);
    m_curState = pState;
    LOGI("GameFSM %s --> %s.", oldStateName, pState->getName());
}

void GameFSM::addState(GameState* pState)
{
    pState->init();
    m_states[m_numStates++] = pState;
}