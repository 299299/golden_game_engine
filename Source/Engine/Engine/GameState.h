#pragma once


#define MAX_GAME_STATES     (32)

class GameState
{
public:
    GameState();
    virtual ~GameState();

    virtual const char* get_name() = 0;
    virtual void init() {};
    virtual void pre_step(float dt){};
    virtual void step(float dt) {};
    virtual void post_step(float dt){};
    virtual void render() {};
    virtual void on_enter(GameState* prev_state) {};
    virtual void on_exit(GameState* next_state) {};
};

class GameFSM
{
public:
    GameFSM();
    ~GameFSM();

    void init();
    void quit();
    void add_state(GameState* p_state);
    void change_state(const char* name);
    GameState* find_state(const char* name) const;

    void pre_step(float dt);
    void step(float dt);
    void post_step(float dt);
    void render(float dt);

private:
    GameState*          m_state;
    GameState**         m_states[MAX_GAME_STATES];
    int                 m_numStates;
};

extern GameFSM g_gameFSM;