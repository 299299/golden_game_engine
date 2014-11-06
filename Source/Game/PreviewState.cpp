#include "PreviewState.h"
#include "Camera.h"
#include "Win32Context.h"
#include "Profiler.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include <bgfx/bgfx.h>

static uint32_t g_bgfx_debug = BGFX_DEBUG_TEXT;
static bool g_show_profile = false;
static bool g_draw_debug_graphics = false;

extern DebugFPSCamera  g_fpsCamera;

PreviewState::PreviewState()
{

}

PreviewState::~PreviewState()
{

}

void PreviewState::step( float dt )
{
    __super::step(dt);
    g_fpsCamera.update(dt);

    if(g_win32Context.is_key_just_pressed(VK_F1))
    {
        bool is_wireframe = HAS_BITS(g_bgfx_debug,BGFX_DEBUG_WIREFRAME);
        is_wireframe = !is_wireframe;
        if(is_wireframe) ADD_BITS(g_bgfx_debug, BGFX_DEBUG_WIREFRAME);
        else REMOVE_BITS(g_bgfx_debug, BGFX_DEBUG_WIREFRAME);
    }
    else if(g_win32Context.is_key_just_pressed(VK_F2))
    {
        g_show_profile = !g_show_profile;
    }
    else if(g_win32Context.is_key_just_pressed(VK_F3))
    {
        g_draw_debug_graphics = !g_draw_debug_graphics;
    }

    if(g_show_profile)
    {
        g_profiler.dump();
    }
    if(g_draw_debug_graphics)
    {
        extern void draw_debug_models();
        extern void draw_debug_lights();
        draw_debug_lights();
        draw_debug_models();
    }
}

void PreviewState::on_enter( GameState* prev_state )
{
    float eye[] = {-5,5,0};
    float at[] = {0,0,0};
    g_camera.update(eye, at);
    g_fpsCamera.set(eye, at);
}
