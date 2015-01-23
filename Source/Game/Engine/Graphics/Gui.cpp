#include "Gui.h"
#include <imgui/imgui.h>
#include "Win32Context.h"
#include "droidsans.ttf.h"
#include "DataDef.h"

Gui     g_guiMgr;
bool    g_smallDebugDraw = false;
int     g_dbgTexIndex = 0;

void Gui::init()
{
    imguiCreate(s_droidSansTtf, sizeof s_droidSansTtf);
}

void Gui::frame_start()
{
    imguiBeginFrame(g_win32Context.m_mx
        , g_win32Context.m_my
        , (g_win32Context.m_mouseStatus[kMouseLeft] ? IMGUI_MBUT_LEFT : 0)
        | (g_win32Context.m_mouseStatus[kMouseRight] ? IMGUI_MBUT_RIGHT : 0)
        , 0
        , g_win32Context.m_width
        , g_win32Context.m_height
        , kGUIViewId);

    bgfx::dbgTextClear(0, g_smallDebugDraw);
    g_dbgTexIndex = 0;
}

void Gui::frame_end()
{
    imguiEndFrame();
}

void Gui::update(float dt)
{

}

void Gui::draw()
{

}

void Gui::shutdown()
{
    imguiDestroy();
}