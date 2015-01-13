#pragma once
#include "Prerequisites.h"
#ifdef HAVOK_COMPILE
#include <Windows.h>
#include <Windowsx.h>
#endif

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
    uint32_t        m_style;
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

    void create_window(const char* title, uint32_t w, uint32_t h);
    void destroy_window();
    void frame_start();
    void reset();

    //---------------------------------------------------------------
    // SET
    void set_mouse_pos(int32_t _mx, int32_t _my);
    void set_window_size(uint32_t _width, uint32_t _height);
    void toggle_window_frame();
    //----------------------------------------------------------------

    //---------------------------------------------------------------
    // GET
    bool is_key_just_pressed(int key_code) const { return m_keyJustPressed[key_code];};
    bool is_key_down(int key_code) const { return m_keyStatus[key_code];};
    bool is_size_changed() const { return m_sizeChanged; };
    bool is_mouse_down(int mouse_button) const { return m_mouseStatus[mouse_button];};
    bool is_mouse_just_pressed(int mouse_button) const { return m_mouseStatus[mouse_button];};
    bool is_window_closed() const { return m_exit; };
    bool is_window_active() const;
    //---------------------------------------------------------------

    LRESULT process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);
private:
    void adjust(uint32_t _width, uint32_t _height, bool _windowFrame);
};

extern Win32Context g_win32Context;
