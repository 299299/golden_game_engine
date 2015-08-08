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
        input.m_axis[0] -= 1.0f;
    if (g_win32Context.is_key_down(VK_RIGHT))
        input.m_axis[0] += 1.0f;
    if (g_win32Context.is_key_down(VK_UP))
        input.m_axis[1] += 1.0f;
    if (g_win32Context.is_key_down(VK_DOWN))
        input.m_axis[1] -= 1.0f;

    update_locomotion(&s_locomotion, input, m_player);

    hkQsTransform t;
    t.setIdentity();

    hkVector4 dir;
    hkVector4 fwd;
    fwd.set(0, 0, 1, 0);
    hkVector4 up;
    up.set(0, 1, 0, 0);

    hkQuaternion rstOut;
    hkSimdFloat32 angle_out = 0;

    dir.setRotatedDir(t.m_rotation, fwd);

    int texColor = RGBCOLOR(255,255,0);
    int idx = 0;

    char buf[256];
    int x = 0;
    int y = 0;
    float ag = 0;

    hkVector4 cam_dir;
    const float *from = g_camera.m_eye;
    const float *to = g_camera.m_at;
    cam_dir.set(from[0] - to[0], 0, from[2] - to[2]);
    cam_dir.normalize3();

    Actor *a = g_actorWorld.get_actor(m_player);

    float camera_angle = hkMath::atan2(cam_dir.getSimdAt(0), cam_dir.getSimdAt(2)) - HK_REAL_PI;
    camera_angle = clamp_angle(camera_angle);

    float input_angle = hkMath::atan2(input.m_axis[0], input.m_axis[1]);
    float character_angle = get_up_axis_angle(a->m_transform.m_rotation);
    float angle_diff = input_angle + camera_angle - character_angle;
    angle_diff = clamp_angle(angle_diff);

    bx::snprintf(buf, sizeof(buf), "input_angle=%f camera_angle=%f character_angle=%f angle_diff=%f",
        input_angle * HK_FLOAT_RAD_TO_DEG,
        camera_angle * HK_FLOAT_RAD_TO_DEG,
        character_angle * HK_FLOAT_RAD_TO_DEG,
        angle_diff * HK_FLOAT_RAD_TO_DEG);
    y += 20;
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, texColor);

    extern void resource_hot_reload_update(float);
    resource_hot_reload_update(dt);

    extern void draw_debug_animation(float);
    draw_debug_animation(dt);

    debug_update_vdb_camera();

    g_debugDrawMgr.add_grid(20, 5, RGBCOLOR(175,175,175), true);
    g_debugDrawMgr.add_axis(hkQsTransform::getIdentity(), 5);
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
        t.setIdentity();
        m_player = g_actorWorld.create_actor(stringid_caculate(actor_name), t);
        LOGD("created actor = %x", m_player);
    }
}
