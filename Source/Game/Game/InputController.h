#pragma once


struct InputController
{
    void init();
    void update(float dt);

    void updateGamePad(float dt);
    void updateKeyboard(float dt);

    //------ all smoothed value -------------
    float               m_leftInput[3];
    float               m_rightInput[3];
    float               m_lastLeftInput[2];
    float               m_leftAngle;
    float               m_leftHoldTime;
};