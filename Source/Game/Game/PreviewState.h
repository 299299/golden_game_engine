#pragma once
#include "GameState.h"
#include "BaseTypes.h"

struct Level;
class PreviewState : public GameState
{
public:
    PreviewState();
    ~PreviewState();

    virtual const char* get_name() const { return "preview"; };
    virtual void step(float dt);
    virtual void on_enter(GameState* prev_state);
    virtual void process_cmd_args(void*);

    ActorId32       m_previewActor;
    Level*          m_previewLevel;
};

