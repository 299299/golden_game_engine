#pragma once
#include "GameState.h"

class RenderViewerState : public GameState
{
public:
    RenderViewerState() {};
    ~RenderViewerState() {};
    virtual const char* getName() const { return "state.renderviewer";};
    virtual void onFirstEnter(GameState* pPrevState);
    virtual void preStep(float timeStep);
    virtual void postStep(float timeStep);
    virtual void render();

private:
    void createPostProcessGUI();
    void createNormalGUI();
};