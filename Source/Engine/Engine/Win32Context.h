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
    int32_t         m_last_mx;
    int32_t         m_last_my;

    bool            m_frame;
    bool            m_exit;

    bool            m_keyJustPressed[255];
    bool            m_keyStatus[255];
    bool            m_mouseStatus[kMouseMax];
    bool            m_mouseJustPressed[kMouseMax];
    bool            m_sizeChanged;
    bool            m_mouseMoved;


    Win32Context();

    void createWindow(const char* title, uint32_t w, uint32_t h);
    void destroyWindow();
    void frame_start();
    void reset();

    //---------------------------------------------------------------
    // SET
    void setMousePos(int32_t _mx, int32_t _my);
    void setWindowSize(uint32_t _width, uint32_t _height);
    void toggleWindowFrame();
    //----------------------------------------------------------------

    //---------------------------------------------------------------
    // GET
    bool isKeyJustPressed(int key_code) const { return m_keyJustPressed[key_code];};
    bool isKeyDown(int key_code) const { return m_keyStatus[key_code];};
    bool isSizeChanged() const { return m_sizeChanged; };
    bool isMouseDown(int mouse_button) const { return m_mouseStatus[mouse_button];};
    bool isMouseJustPressed(int mouse_button) const { return m_mouseStatus[mouse_button];};
    bool isWindowClosed() const { return m_exit; };
    bool isWindowActive() const;
    //---------------------------------------------------------------

    LRESULT process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);
private:
    void adjust(uint32_t _width, uint32_t _height, bool _windowFrame);
};

extern Win32Context g_win32Context;
