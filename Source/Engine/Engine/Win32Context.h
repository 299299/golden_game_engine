#pragma once
#include "Prerequisites.h"
#include <Windows.h>
#include <Windowsx.h>


enum MouseButton
{
    kMouseLeft,
    kMouseMiddle,
    kMouseRight,
    kMouseMax
};

typedef void (*__WIN_SIZE_FUNC_)(uint32_t w, uint32_t h);
typedef void (*__WIN_KEY_FUNC_)(uint32_t key, bool down);
typedef void (*__WIN_MOUSE_BUTTON_FUNC_)(int32_t mx, int32_t my, uint32_t button, bool down);
typedef void (*__WIN_MOUSE_MOVE_FUNC_)(int32_t mx, int32_t my);

struct Win32InputCallback
{
    __WIN_SIZE_FUNC_                m_sizedCallback;
    __WIN_KEY_FUNC_                 m_keyCallback;
    __WIN_MOUSE_BUTTON_FUNC_        m_mouseCallback;
    __WIN_MOUSE_MOVE_FUNC_          m_mouseMoveCallback;
};

#define MAX_WIN32_INPUT_CALLBACK            (10)

struct Win32Context
{
    HWND            m_hwnd;
    HWND            m_parentHwnd;

    RECT            m_rect;
    DWORD           m_style;
    uint32_t        m_width;
    uint32_t        m_height;
    uint32_t        m_oldWidth;
    uint32_t        m_oldHeight;
    uint32_t        m_frameWidth;
    uint32_t        m_frameHeight;
    float           m_aspectRatio;

    uint32_t        m_lastWidth;
    uint32_t        m_lastHeight;

    int32_t         m_mx;
    int32_t         m_my;

    bool            m_frame;
    bool            m_exit;

    bool            m_keyStatus[255];
    bool            m_mouseStatus[kMouseMax];

    Win32InputCallback  m_callbacks[MAX_WIN32_INPUT_CALLBACK];
    int             m_numCallbacks;

    Win32Context();

    void createWindow(const char* title, uint32_t w, uint32_t h);
    void destroyWindow();

    void pollWin32Events();
    inline bool isWindowClosed() const { return m_exit; };
    bool isWindowActive() const;

    void setMousePos(int32_t _mx, int32_t _my);
    void setWindowSize(uint32_t _width, uint32_t _height);
    void toggleWindowFrame();

    LRESULT process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

    int registerCallback(Win32InputCallback cb);
    void unregisterCallback(int index);

private:
    void adjust(uint32_t _width, uint32_t _height, bool _windowFrame);
};

extern Win32Context g_win32Context;
