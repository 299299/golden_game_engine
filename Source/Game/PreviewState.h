#pragma once
#include "GameState.h"


class PreviewState : public GameState
{
public:
    PreviewState();
    ~PreviewState();

    virtual const char* get_name() const { return "preview"; };
    virtual void step(float dt);
};

