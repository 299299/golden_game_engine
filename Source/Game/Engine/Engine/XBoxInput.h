#pragma once

#define MAX_CONNECT_INPUT   (4)

class XInput
{
public:
    XInput();
    ~XInput();
    void update(float timeStep);
    void vibrate(int index, float leftVal, float rightVal, float fTime);
    bool is_button_down(int index, int button) const;
    bool is_button_just_pressed(int index, int button) const;
    
    float get_left_trigger(int index) const;
    float get_right_trigger(int index) const;

    const float* get_ls_raw(int index) const { return m_LSRaw[index]; };
    const float* get_rs_raw(int index) const { return m_RSRaw[index]; };

    const float* get_ls_smooth(int index) const { return m_LSSmooth[index]; };
    const float* get_rs_smooth(int index) const { return m_RSSmooth[index]; };

    int  get_connected_num() const;
    bool is_connected(int index) const { return m_deviceStatus[index]; };

private:
    void update_stick(int index, float timeStep);
    bool check_devices(float timeStep);

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