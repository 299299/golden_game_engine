#pragma once


struct Gui
{
    void init();
    void frameStart();
    void frameEnd();
    void update(float dt);
    void draw();
    void destroy();
};


extern Gui g_guiMgr;