#pragma once
#include "GameState.h"


class PreviewState : public GameState
{
public:
    PreviewState();
    ~PreviewState();

    virtual const char* get_name() const { return "preview"; };
    virtual void step(float dt);
    virtual void on_enter(GameState* prev_state);
};

