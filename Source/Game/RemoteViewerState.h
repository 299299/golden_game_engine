#pragma once
#include "GameState.h"

class RemoteViewerState : public GameState
{
public:
    RemoteViewerState(){};
    ~RemoteViewerState() {};
    virtual const char* getName() const { return "state.remoteviewer"; };
    virtual void init();
    virtual void onFirstEnter(GameState* pPrevState);
    virtual void frameStart(float timeStep);
    virtual void preStep(float timeStep);
    virtual void postStep(float timeStep);
    StringId        m_previewPackageName;
};
