#pragma once
#include "GameState.h"

class TestGameState : public GameState
{
public:
    TestGameState();
    ~TestGameState();
    virtual const char* getName() const { return "state.testgame";};
    virtual void onFirstEnter(GameState* pPrevState);
    virtual void preStep(float timeStep);
    virtual void postStep(float timeStep);
	virtual void render();
};