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

#ifdef HAVOK_COMPILE
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

    g_debugDrawMgr.add_grid(20, 5, RGBCOLOR(175,175,175), true);

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

    #define G_DEBUG_OUT \
    t.m_rotation.setAxisAngle(up, ag); \
    bx::snprintf(buf, sizeof(buf), "[%d] angle=%f vs %f", \
        idx++, \
        ag * HK_FLOAT_RAD_TO_DEG, \
        get_up_axis_angle(t.m_rotation) * HK_FLOAT_RAD_TO_DEG); \
    y += 20; \
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, texColor);

    ag = 0;
    G_DEBUG_OUT

    ag = HK_REAL_PI/2;
    G_DEBUG_OUT

    ag = HK_REAL_PI;    
    G_DEBUG_OUT

    ag = HK_REAL_PI*3/2;
    G_DEBUG_OUT

    ag = HK_REAL_PI*2;
    G_DEBUG_OUT
  
    ENGINE_NATIVE_ALIGN(float   invView[16]);
    bx::mtxInverse(invView, g_camera.m_view);
    t.set4x4ColumnMajor(invView);
    t.m_translation.setZero4();
    float camera_angle = get_up_axis_angle(t.m_rotation);
    float input_angle = hkMath::atan2(input.m_axis[0], input.m_axis[1]);
    input_angle = clamp_angle(input_angle);
    Actor *a = g_actorWorld.get_actor(m_player);
    float cur_angle = get_up_axis_angle(a->m_transform.m_rotation);
    float dst_angle = input_angle + camera_angle;
    dst_angle = clamp_angle(dst_angle);
    float angle_diff = dst_angle - cur_angle;
    //angle_diff = clamp_angle(angle_diff);

    bx::snprintf(buf, sizeof(buf), "input angle=%f camera=%f dst_angle=%f cur_angle=%f angle_diff=%f", 
        input_angle * HK_FLOAT_RAD_TO_DEG, 
        camera_angle * HK_FLOAT_RAD_TO_DEG, 
        dst_angle * HK_FLOAT_RAD_TO_DEG,
        cur_angle * HK_FLOAT_RAD_TO_DEG, 
        angle_diff * HK_FLOAT_RAD_TO_DEG);
    y += 20;
    imguiDrawText(x, y, ImguiTextAlign::Left, buf, texColor);

    extern void resource_hot_reload_update(float);
    resource_hot_reload_update(dt);

    extern void draw_debug_animation(float);
    draw_debug_animation(dt);

    debug_update_vdb_camera();

    g_debugDrawMgr.add_axis(hkQsTransform::getIdentity(), 5);
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
