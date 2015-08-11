#include "InputController.h"
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
#include "RenderCamera.h"
#include "AnimRig.h"
#include "Win32Context.h"
#include "XBoxInput.h"
#include "MathDefs.h"
#include "Log.h"

#define KEY_INPUT_GAIN      (10.0f)
#define MOUSE_INPUT_GAIN    (10.0f)

void InputController::init()
{
    memset(this, 0x00, sizeof(InputController));
}

void InputController::update(float dt)
{
    if(g_XInput.is_connected(0))
        updateGamePad(dt);
    else
        updateKeyboard(dt);

    m_leftAngle = hkMath::atan2( m_leftInput[0], m_leftInput[1] );
    m_leftInput[2] = hkMath::sqrt(m_leftInput[0] * m_leftInput[0] + m_leftInput[1] * m_leftInput[1]);
    m_rightInput[2] = hkMath::sqrt(m_rightInput[0] * m_rightInput[0] + m_rightInput[1] * m_rightInput[1]);

    float xdiff = m_lastLeftInput[0] - m_leftInput[0];
    float ydiff = m_lastLeftInput[1] - m_lastLeftInput[1];
    float diff = xdiff * xdiff + ydiff * ydiff;
    if(diff < 0.1f)
        m_leftHoldTime += dt;
    else
        m_leftHoldTime = 0;

    m_lastLeftInput[0] = m_leftInput[0];
    m_lastLeftInput[1] = m_leftInput[1];
}


void InputController::updateGamePad(float dt)
{
    const float* linput = g_XInput.get_ls_smooth(0);
    m_leftInput[0] = linput[0];
    m_leftInput[1] = linput[1];

    const float* rinput = g_XInput.get_rs_smooth(0);
    m_rightInput[0] = rinput[0];
    m_rightInput[1] = rinput[1];
}

void InputController::updateKeyboard(float dt)
{
    float keyInput[2] = {0.0f, 0.0f};
    const int keyMap[4] = { VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN };
    if(g_win32Context.is_key_down(keyMap[0]))
        keyInput[0] += -1.0f;
    if(g_win32Context.is_key_down(keyMap[1]))
        keyInput[0] += +1.0f;
    if(g_win32Context.is_key_down(keyMap[2]))
        keyInput[1] += 1.0f;
    if(g_win32Context.is_key_down(keyMap[3]))
        keyInput[1] += -1.0f;

    m_leftInput[0] = bx::flerp(m_leftInput[0], keyInput[0], dt*KEY_INPUT_GAIN);
    m_leftInput[1] = bx::flerp(m_leftInput[1], keyInput[1], dt*KEY_INPUT_GAIN);

    float mx = (float)g_win32Context.m_mx / (float)g_win32Context.m_width;
    float my = (float)g_win32Context.m_my / (float)g_win32Context.m_height;
    float mouseInput[2] = {mx - 0.5f, my - 0.5f };
    m_rightInput[0] = bx::flerp(m_rightInput[0], mouseInput[0], dt*MOUSE_INPUT_GAIN);
    m_rightInput[1] = bx::flerp(m_rightInput[1], mouseInput[1], dt*MOUSE_INPUT_GAIN);

    if (m_lockMouse)
        g_win32Context.set_mouse_pos(g_win32Context.m_width/2, g_win32Context.m_height/2);
}