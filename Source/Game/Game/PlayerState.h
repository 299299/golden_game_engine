#pragma once
#include "GameState.h"
#include "BaseTypes.h"
#include "StringId.h"

class PlayerState : public GameState
{
public:
    PlayerState();
    ~PlayerState();

    virtual const char* get_name() const { return "player"; };
    virtual void step(float dt);
    virtual void on_enter(GameState* prev_state);
     virtual void process_cmd_args(void*);

private:
    ActorId32               m_player;
};

