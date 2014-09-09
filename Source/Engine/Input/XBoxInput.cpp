#include "XBoxInput.h"
#include "Prerequisites.h"
#include "Log.h"
#include <Windows.h>
#include <XInput.h>
#include "Profiler.h"

#define VIBRATION_MAX               (65535.0f)
#define XINPUT_DEVICE_TIMER         (2.0f)
#ifndef XUSER_MAX_COUNT
#define XUSER_MAX_COUNT             (4)
#endif

static  bool                        g_status[XUSER_MAX_COUNT];
static  XINPUT_STATE                g_states[XUSER_MAX_COUNT];

XInput g_XInput;

XInput::XInput()
    :m_deviceTimer(0)
{
    memset(g_states, 0x00, sizeof(g_states));
    memset(m_deviceStatus, 0x00, sizeof(m_deviceStatus));

    memset(m_LSRaw, 0x00, sizeof(m_LSRaw));
    memset(m_RSRaw, 0x00, sizeof(m_RSRaw));
    memset(m_LSSmooth, 0x00, sizeof(m_LSSmooth));
    memset(m_RSSmooth, 0x00, sizeof(m_RSSmooth));
    memset(m_vibrateTime, 0x00, sizeof(m_vibrateTime));
    for (unsigned i=0; i<XUSER_MAX_COUNT; ++i)
    {
        m_deviceStatus[i] = (XInputGetState(i, &g_states[i]) == ERROR_SUCCESS);
    }
}

XInput::~XInput()
{

}

void XInput::vibrate( int index, float leftVal, float rightVal, float fTime )
{
    if(!isConnected(index))
        return;
    if(fTime <= 0.0f)
        return;
    leftVal = hkMath::clamp<float>(leftVal, 0.0f, 1.0f);
    rightVal = hkMath::clamp<float>(rightVal, 0.0f, 1.0f);
    XINPUT_VIBRATION tmpVibration;
    tmpVibration.wLeftMotorSpeed = (WORD)(leftVal * VIBRATION_MAX);
    tmpVibration.wRightMotorSpeed = (WORD)(rightVal * VIBRATION_MAX);
    m_vibrateTime[index] = fTime;
    XInputSetState(index, &tmpVibration);
}

bool XInput::isButtonDown(int index, int button ) const
{
    if(!isConnected(index))
        return false;
    return (g_states[index].Gamepad.wButtons & button) != 0;
}

bool XInput::checkDevices(float timeStep)
{
    bool bRet = false;
    m_deviceTimer += timeStep;
    if(m_deviceTimer < XINPUT_DEVICE_TIMER)
        return bRet;

    m_deviceTimer = 0.0f;
    for (unsigned i=0; i<XUSER_MAX_COUNT; ++i)
    {
        g_status[i] = (XInputGetState(i, &g_states[i]) == ERROR_SUCCESS);
        if(g_status[i] != m_deviceStatus[i])
        {
            bRet = true;
            LOGD("XBOX 360 Controller device status has %s", g_status[i] ? "connected" : "disconnected.");
            m_deviceStatus[i] = g_status[i];
        }
    }
    return bRet;
}

void XInput::update( float timeStep )
{
    checkDevices(timeStep);

    for (int i=0; i<XUSER_MAX_COUNT;++i)
    {
        updateStick(i, timeStep);
    }
}

int XInput::getConnectedNum() const
{
    int iRet = 0;
    for (int i=0; i<XUSER_MAX_COUNT;++i)
    {
        if(m_deviceStatus[i])
            ++iRet;
    }
    return iRet;
}

float XInput::getLeftTrigger( int index ) const
{
    if(!isConnected(index))
        return 0.0f;
    float t = (float)g_states[index].Gamepad.bLeftTrigger;
    if(t <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        return 0.0f;
    return (t - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (255.0f - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

float XInput::getRightTrigger( int index ) const
{
    if(!isConnected(index))
        return 0.0f;
    float t = (float)g_states[index].Gamepad.bRightTrigger;
    if(t <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        return 0.0f;
    return (t - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (255.0f - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

void caculateValue(short tx, short ty, float deadZone, float* outValue)
{
    float LX = (float)tx;
    float LY = (float)ty;

    //determine how far the controller is pushed
    float magnitude = sqrt(LX*LX + LY*LY);

    //determine the direction the controller is pushed
    float normalizedLX = LX / magnitude;
    float normalizedLY = LY / magnitude;

    float normalizedMagnitude;

    //check if the controller is outside a circular dead zone
    if (magnitude > deadZone)
    {
        //clip the magnitude at its expected maximum value
        if (magnitude > 32767.0f)
            magnitude = 32767.0f;

        //adjust magnitude relative to the end of the dead zone
        magnitude -= deadZone;

        //optionally normalize the magnitude with respect to its expected range
        //giving a magnitude value of 0.0 to 1.0
        normalizedMagnitude = magnitude / (32767.0f - deadZone);
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
        magnitude = 0.0f;
        normalizedMagnitude = 0.0f;

        if(abs(tx) < deadZone) 
            normalizedLX = 0.0f;
        if(abs(ty) < deadZone)
            normalizedLY = 0.0f;
    }
    outValue[0] = normalizedLX;
    outValue[1] = normalizedLY;
}

void XInput::updateStick( int index, float timeStep )
{
    const XINPUT_GAMEPAD& xGamePad = g_states[index].Gamepad;
    caculateValue(xGamePad.sThumbLX,  xGamePad.sThumbLY,  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, m_LSSmooth[index]);
    caculateValue(xGamePad.sThumbRX, xGamePad.sThumbRY,  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, m_RSSmooth[index]);

    m_LSRaw[index][0] = (float)xGamePad.sThumbLX/32767.0f;
    m_LSRaw[index][1] = (float)xGamePad.sThumbLY/32767.0f;

    m_RSRaw[index][0] = (float)xGamePad.sThumbRX/32767.0f;
    m_RSRaw[index][1] = (float)xGamePad.sThumbRY/32767.0f;

    float oldTime = m_vibrateTime[index];
    float& vTime = m_vibrateTime[index];
    vTime -= timeStep;
    if(vTime < 0.0f)
        vTime = 0.0f;
    if(oldTime > 0.0f && vTime <= 0.0f)
    {
        XINPUT_VIBRATION tmpVibration;
        ZeroMemory(&tmpVibration, sizeof(tmpVibration));
        XInputSetState((DWORD)index, &tmpVibration);
    }
}


