#pragma once
#include "Prerequisites.h"
#include "StringId.h"

struct ShadingEnviroment;
class GameState
{
public:
    GameState();
    virtual ~GameState() = 0 {};
    virtual const char* getName() const = 0;
    virtual void init() { m_nameId = StringId(getName()); };
    virtual void onEnter(GameState* pPrevState);
    virtual void onExit(GameState* pNextState) {};

    virtual void preStep(float timeStep);
    virtual void step(float timeStep);
    virtual void postStep(float timeStep);
    virtual void frameStart(float timeStep);
    virtual void render();
    virtual void frameEnd(float timeStep);
    virtual void onFirstEnter(GameState* pPrevState) {};

    virtual void dbgPrintfEngineStatus(bool bDumpProfiler = true);

    StringId                    m_nameId;
    StringId                    m_nextStateName;
    float                       m_timeInState;
    ShadingEnviroment*          m_shading;
    bool                        m_hasEntered;
};