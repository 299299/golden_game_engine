#pragma once
#include "Prerequisites.h"
#include "StringId.h"

#define GAME_STATE_NUM          (16)

class GameState;

class GameFSM
{
public:
    void init();
    void quit();

    void frameStart(float timeStep);
    void preStep(float timeStep);
    void step(float timeStep);
    void postStep(float timeStep);
    void render();
    void frameEnd(float timeStep);

    GameState* findState(const StringId& name) const;
    void changeState(const StringId& name);
    void changeState(GameState* pState);
    void addState(GameState* pState);

    GameState*                      m_states[GAME_STATE_NUM];
    GameState*                      m_curState;
    int                             m_numStates;
};


extern GameFSM g_gameFSM;