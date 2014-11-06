#pragma once
#include "GameState.h"


class PlayerState : public GameState
{
public:
    PlayerState();
    ~PreviewState();

    virtual const char* get_name() const { return "player"; };
    virtual void step(float dt);
};

