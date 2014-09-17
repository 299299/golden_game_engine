#pragma once


struct Gui
{
    void init();
    void frame_start();
    void frame_end();
    void update(float dt);
    void draw();
    void destroy();
};


extern Gui g_guiMgr;
extern int g_dbgTexIndex;

#define DBG_TEX_PRINTF(color, ...) bgfx::dbgTextPrintf(0, g_dbgTexIndex++, color, __VA_ARGS__)