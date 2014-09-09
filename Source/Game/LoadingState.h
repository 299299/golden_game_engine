#pragma once
#include "GameState.h"

class LoadingState : public GameState
{
public:
    LoadingState() {};
    ~LoadingState() {};
    virtual const char* getName() const { return "state.loading";};
    virtual void onEnter(GameState* pPrevState);
    virtual void preStep(float timeStep);
    virtual void postStep(float timeStep);
    virtual void render();
    void setLoadingPackage(const char* packageName);
    void setLoadingFinishState(const StringId& stateName);
private:
    const char*         m_packageName;
    StringId            m_loadPackageName;
    StringId            m_finishStateName;
};