#include <imgui/imgui.h>
#include "PlayerState.h"
#include "RenderCamera.h"
#include "Profiler.h"
#include "Model.h"
#include "Light.h"
#include "RenderCamera.h"
#include "DebugDraw.h"
#include "Log.h"
#include "Actor.h"
#include "Animation.h"
#include "Resource.h"
#include "Win32Context.h"
#include "AnimRig.h"
#include "Component.h"
#include "Level.h"
#include "AnimationState.h"
#include "AnimControl.h"
#include "AnimationSystem.h"
#include "Engine.h"
#include "Locomotion.h"
#include <bx/string.h>
#include <bx/commandline.h>

extern DebugFPSCamera  g_fpsCamera;

static Locomotion s_locomotion = { 0 };

PlayerState::PlayerState()
:m_player(INVALID_U32)
{

}

PlayerState::~PlayerState()
{

}

void PlayerState::step(float dt)
{
    GameState::step(dt);
    g_fpsCamera.update(dt);


    LocomotionInput input = { dt, 0, 0 };
    if (g_win32Context.is_key_down(VK_LEFT))
        input.m_vec[0] -= 1.0f;
    if (g_win32Context.is_key_down(VK_RIGHT))
        input.m_vec[0] += 1.0f;
    if (g_win32Context.is_key_down(VK_UP))
        input.m_vec[1] += 1.0f;
    if (g_win32Context.is_key_down(VK_DOWN))
        input.m_vec[1] -= 1.0f;

    update_locomotion(&s_locomotion, input, m_player);

    g_debugDrawMgr.add_grid(20, 5, RGBCOLOR(175,175,175), true);

    hkQsTransform t;
    t.setIdentity();

    hkVector4 dir;
    hkVector4 fwd;
    fwd.set(0, 0, 1, 0);
    hkVector4 up;
    up.set(0, 1, 0, 0);

    dir.setRotatedDir(t.m_rotation, fwd);

    char buf[256];
    t.m_rotation.setAxisAngle(up, 0);
    dir.setRotatedDir(t.m_rotation, fwd);
    bx::snprintf(buf, sizeof(buf), "[0] %f, %f, %f angle=%f", dir(0), dir(1), dir(2), hkMath::atan2(dir(1), dir(0)));
    int x = 0;
    int y = 15;
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, RGBCOLOR(255,0,0));

    y += 20;
    t.m_rotation.setAxisAngle(up, 90);
    dir.setRotatedDir(t.m_rotation, fwd);
    bx::snprintf(buf, sizeof(buf), "[90] %f, %f, %f angle=%f", dir(0), dir(1), dir(2), hkMath::atan2(dir(1), dir(0)));
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, RGBCOLOR(255,0,0));

    y += 20;
    t.m_rotation.setAxisAngle(up, 180);
    dir.setRotatedDir(t.m_rotation, fwd);
    bx::snprintf(buf, sizeof(buf), "[180] %f, %f, %f angle=%f", dir(0), dir(1), dir(2), hkMath::atan2(dir(1), dir(0)));
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, RGBCOLOR(255,0,0));

    y += 20;
    t.m_rotation.setAxisAngle(up, 270);
    dir.setRotatedDir(t.m_rotation, fwd);
    bx::snprintf(buf, sizeof(buf), "[270] %f, %f, %f angle=%f", dir(0), dir(1), dir(2), hkMath::atan2(dir(1), dir(0)));
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, RGBCOLOR(255,0,0));

    y += 20;
    t.m_rotation.setAxisAngle(up, 360);
    dir.setRotatedDir(t.m_rotation, fwd);
    bx::snprintf(buf, sizeof(buf), "[360] %f, %f, %f angle=%f", dir(0), dir(1), dir(2), hkMath::atan2(dir(1), dir(0)));
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, RGBCOLOR(255,0,0));

    y += 20;
    transform_matrix(t, g_camera.m_view);
    dir.setRotatedDir(t.m_rotation, fwd);
    bx::snprintf(buf, sizeof(buf), "[Camera] %f, %f, %f angle=%f", dir(0), dir(1), dir(2), hkMath::atan2(dir(1), dir(0)));
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, RGBCOLOR(255,0,0));

    extern void resource_hot_reload_update(float);
    resource_hot_reload_update(dt);

    extern void draw_debug_animation(float);
    draw_debug_animation(dt);

    debug_update_vdb_camera();


#ifdef HAVOK_COMPILE
    g_debugDrawMgr.add_axis(hkQsTransform::getIdentity());
#endif
}

void PlayerState::on_enter( GameState* prev_state )
{
    LOGD("player-state-enter");
    float eye[] = {0,5,-5};
    float at[] = {0,0,0};
    g_camera.update(eye, at);
    g_fpsCamera.set(eye, at);
}

void PlayerState::process_cmd_args( void* p )
{
    bx::CommandLine* cmd = (bx::CommandLine*)p;
    const char* actor_name = cmd->findOption("actor");

    if(actor_name)
    {
        LOGD("loading actor %s \n", actor_name);
        hkQsTransform t;
#ifdef HAVOK_COMPILE
        t.setIdentity();
#endif
        m_player = g_actorWorld.create_actor(stringid_caculate(actor_name), t);
        LOGD("created actor = %x", m_player);
    }
}
