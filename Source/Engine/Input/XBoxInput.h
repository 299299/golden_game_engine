#pragma once

#define MAX_CONNECT_INPUT   (4)

class XInput
{
public:
    XInput();
    ~XInput();
    void update(float timeStep);
    void vibrate(int index, float leftVal, float rightVal, float fTime);
    bool isButtonDown(int index, int button) const;
    
    float getLeftTrigger(int index) const;
    float getRightTrigger(int index) const;

    inline const float* getLSRaw(int index) const { return m_LSRaw[index]; };
    inline const float* getRSRaw(int index) const { return m_RSRaw[index]; };

    inline const float* getLSSmooth(int index) const { return m_LSSmooth[index]; };
    inline const float* getRSSmooth(int index) const { return m_RSSmooth[index]; };

    int  getConnectedNum() const;
    inline bool isConnected(int index) const { return m_deviceStatus[index]; };

private:
    void updateStick(int index, float timeStep);
    bool checkDevices(float timeStep);

private:
    float                       m_deviceTimer;
    bool                        m_deviceStatus[MAX_CONNECT_INPUT];

    float                       m_vibrateTime[MAX_CONNECT_INPUT];

    float                       m_LSRaw[MAX_CONNECT_INPUT][2];
    float                       m_RSRaw[MAX_CONNECT_INPUT][2];

    float                       m_LSSmooth[MAX_CONNECT_INPUT][2];
    float                       m_RSSmooth[MAX_CONNECT_INPUT][2];
};

extern XInput g_XInput;