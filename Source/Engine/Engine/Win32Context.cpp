#include "Win32Context.h"
#include "DataDef.h"
#include <bx/uint32_t.h>

#define WM_USER_SET_WINDOW_SIZE     (WM_USER+0)
#define WM_USER_TOGGLE_WINDOW_FRAME (WM_USER+1)

static int g_baseWidth = 1280;
static int g_baseHeight = 720;

Win32Context g_win32Context;

LRESULT CALLBACK win32_wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
{
    return g_win32Context.process(_hwnd, _id, _wparam, _lparam);
}

Win32Context::Win32Context()
{
    memset(this, 0x00, sizeof(Win32Context));
    m_frame = true;
}

void Win32Context::createWindow(const char* title, uint32_t w, uint32_t h)
{
    SetDllDirectory(".");

    g_baseWidth = w;
    g_baseHeight = h;

    HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

    WNDCLASSEX wnd;
    memset(&wnd, 0, sizeof(wnd) );
    wnd.cbSize = sizeof(wnd);
    wnd.lpfnWndProc = DefWindowProc;
    wnd.hInstance = instance;
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wnd.lpszClassName = "engine_letterbox";
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassExA(&wnd);

    memset(&wnd, 0, sizeof(wnd) );
    wnd.cbSize = sizeof(wnd);
    wnd.style = CS_HREDRAW | CS_VREDRAW;
    wnd.lpfnWndProc = win32_wndProc;
    wnd.hInstance = instance;
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd.lpszClassName = "engine_window_class";
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassExA(&wnd);

    m_parentHwnd = CreateWindowA("engine_letterbox"
        , "Engine_Frame"
        , WS_POPUP|WS_SYSMENU
        , -32000
        , -32000
        , 0
        , 0
        , NULL
        , NULL
        , instance
        , 0
        );

    m_hwnd = CreateWindowA("engine_window_class"
        , title
        , WS_OVERLAPPEDWINDOW|WS_VISIBLE
        , 0
        , 0
        , w
        , h
        , m_parentHwnd
        , NULL
        , instance
        , 0
        );

    adjust(w, h, true);
    m_width = w;
    m_height = h;
    m_oldWidth = w;
    m_oldHeight = h;
    m_lastWidth = w;
    m_lastHeight = h;
}

void Win32Context::destroyWindow()
{
    DestroyWindow(m_hwnd);
    DestroyWindow(m_parentHwnd);
}

void Win32Context::pollWin32Events()
{
    if(m_exit) return;
	MSG msg;
    while (0 != PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    if(m_lastWidth != m_width || m_lastHeight != m_height)
    {
        for (int i=0; i<m_numCallbacks; ++i)
        {
            if(m_callbacks[i].m_sizedCallback)
                m_callbacks[i].m_sizedCallback(m_width, m_height);
        }
        m_lastWidth = m_width;
        m_lastHeight = m_height;
    }
}

bool Win32Context::isWindowActive() const
{
    HWND hwnd = GetForegroundWindow();
    return (hwnd == m_hwnd) || (hwnd == m_parentHwnd);
}

void Win32Context::adjust(uint32_t _width, uint32_t _height, bool _windowFrame)
{
    m_width = _width;
    m_height = _height;
    m_aspectRatio = float(_width)/float(_height);

    ShowWindow(m_hwnd, SW_SHOWNORMAL);
    RECT rect;
    RECT newrect = {0, 0, (LONG)_width, (LONG)_height};
    DWORD style = WS_POPUP|WS_SYSMENU;

    if (m_frame)
    {
        GetWindowRect(m_hwnd, &m_rect);
        m_style = GetWindowLong(m_hwnd, GWL_STYLE);
    }

    if (_windowFrame)
    {
        rect = m_rect;
        style = m_style;
    }
    else
    {
        HMONITOR monitor = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mi;
        mi.cbSize = sizeof(mi);
        GetMonitorInfo(monitor, &mi);
        newrect = mi.rcMonitor;
        rect = mi.rcMonitor;
    }

    SetWindowLong(m_hwnd, GWL_STYLE, style);
    uint32_t prewidth = newrect.right - newrect.left;
    uint32_t preheight = newrect.bottom - newrect.top;
    AdjustWindowRect(&newrect, style, FALSE);
    m_frameWidth = (newrect.right - newrect.left) - prewidth;
    m_frameHeight = (newrect.bottom - newrect.top) - preheight;
    UpdateWindow(m_hwnd);

    if (rect.left == -32000
    ||  rect.top == -32000)
    {
        rect.left = 0;
        rect.top = 0;
    }

    int32_t left = rect.left;
    int32_t top = rect.top;
    int32_t width = (newrect.right-newrect.left);
    int32_t height = (newrect.bottom-newrect.top);

    if (!_windowFrame)
    {
        float aspectRatio = 1.0f/m_aspectRatio;
        width = bx::uint32_max(_width/4, width);
        height = uint32_t(float(width)*aspectRatio);

        left = newrect.left+(newrect.right-newrect.left-width)/2;
        top = newrect.top+(newrect.bottom-newrect.top-height)/2;
    }

    HWND parent = GetWindow(m_hwnd, GW_OWNER);
    if (NULL != parent)
    {
        if (_windowFrame)
        {
            SetWindowPos(parent
                , HWND_TOP
                , -32000
                , -32000
                , 0
                , 0
                , SWP_SHOWWINDOW
                );
        }
        else
        {
            SetWindowPos(parent
                , HWND_TOP
                , newrect.left
                , newrect.top
                , newrect.right-newrect.left
                , newrect.bottom-newrect.top
                , SWP_SHOWWINDOW
                );
        }
    }

    SetWindowPos(m_hwnd
        , HWND_TOP
        , left
        , top
        , width
        , height
        , SWP_SHOWWINDOW
        );

    ShowWindow(m_hwnd, SW_RESTORE);

    m_frame = _windowFrame;
}

void Win32Context::setMousePos(int32_t _mx, int32_t _my)
{
    POINT pt = { _mx, _my };
    ClientToScreen(m_hwnd, &pt);
    SetCursorPos(pt.x, pt.y);   
}

void Win32Context::setWindowSize(uint32_t _width, uint32_t _height)
{
    PostMessage(m_hwnd, WM_USER_SET_WINDOW_SIZE, 0, (_height<<16) | (_width&0xffff) );
}

void Win32Context::toggleWindowFrame()
{
    PostMessage(m_hwnd, WM_USER_TOGGLE_WINDOW_FRAME, 0, 0);
}

LRESULT Win32Context::process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
{
switch (_id)
    {
    case WM_USER_SET_WINDOW_SIZE:
        {
            uint32_t width = GET_X_LPARAM(_lparam);
            uint32_t height = GET_Y_LPARAM(_lparam);
            adjust(width, height, true);
        }
        break;

    case WM_USER_TOGGLE_WINDOW_FRAME:
        {
            if (m_frame)
            {
                m_oldWidth = m_width;
                m_oldHeight = m_height;
            }
            adjust(m_oldWidth, m_oldHeight, !m_frame);
        }
        break;

    case WM_DESTROY:
        break;

    case WM_QUIT:
    case WM_CLOSE:
        m_exit = true;
        break;

    case WM_SIZING:
        {
            RECT& rect = *(RECT*)_lparam;
            uint32_t width = rect.right - rect.left - m_frameWidth;
            uint32_t height = rect.bottom - rect.top - m_frameHeight;

            //Recalculate size according to aspect ratio
            switch (_wparam)
            {
            case WMSZ_LEFT:
            case WMSZ_RIGHT:
                {
                    float aspectRatio = 1.0f/m_aspectRatio;
                    width = bx::uint32_max(g_baseWidth/4, width);
                    height = uint32_t(float(width)*aspectRatio);
                }
                break;

            default:
                {
                    float aspectRatio = m_aspectRatio;
                    height = bx::uint32_max(g_baseHeight/4, height);
                    width = uint32_t(float(height)*aspectRatio);
                }
                break;
            }

            //Recalculate position using different anchor points
            switch(_wparam)
            {
            case WMSZ_LEFT:
            case WMSZ_TOPLEFT:
            case WMSZ_BOTTOMLEFT:
                rect.left = rect.right - width - m_frameWidth;
                rect.bottom = rect.top + height + m_frameHeight;
                break;

            default:
                rect.right = rect.left + width + m_frameWidth;
                rect.bottom = rect.top + height + m_frameHeight;
                break;
            }
            
        }
        return 0;

    case WM_SIZE:
        {
            uint32_t width = GET_X_LPARAM(_lparam);
            uint32_t height = GET_Y_LPARAM(_lparam);

            m_width = width;
            m_height = height;
        }
        break;

    case WM_SYSCOMMAND:
        switch (_wparam)
        {
        case SC_MINIMIZE:
        case SC_RESTORE:
            {
                HWND parent = GetWindow(_hwnd, GW_OWNER);
                if (NULL != parent)
                {
                    PostMessage(parent, _id, _wparam, _lparam);
                }
            }
        }
        break;

    case WM_MOUSEMOVE:
        {
            int32_t mx = GET_X_LPARAM(_lparam);
            int32_t my = GET_Y_LPARAM(_lparam);
            m_mx = mx;
            m_my = my;
            for (int i=0; i<m_numCallbacks; ++i)
            {
                if(m_callbacks[i].m_mouseMoveCallback)
                    m_callbacks[i].m_mouseMoveCallback(mx, my);
            }
        }
        break;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
        {
            int32_t mx = GET_X_LPARAM(_lparam);
            int32_t my = GET_Y_LPARAM(_lparam);
            m_mouseStatus[kMouseLeft] = _id == WM_LBUTTONDOWN;
            for (int i=0; i<m_numCallbacks; ++i)
            {
                if(m_callbacks[i].m_mouseCallback)
                    m_callbacks[i].m_mouseCallback(mx, my, kMouseLeft, _id == WM_LBUTTONDOWN);
            }
        }
        break;

    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
        {
            int32_t mx = GET_X_LPARAM(_lparam);
            int32_t my = GET_Y_LPARAM(_lparam);
            m_mouseStatus[kMouseMiddle] = _id == WM_MBUTTONDOWN;
            for (int i=0; i<m_numCallbacks; ++i)
            {
                if(m_callbacks[i].m_mouseCallback)
                    m_callbacks[i].m_mouseCallback(mx, my, kMouseMiddle, _id == WM_MBUTTONDOWN);
            }
        }
        break;

    case WM_RBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONDBLCLK:
        {
            int32_t mx = GET_X_LPARAM(_lparam);
            int32_t my = GET_Y_LPARAM(_lparam);
            m_mouseStatus[kMouseRight] = _id == WM_RBUTTONDOWN;
            for (int i=0; i<m_numCallbacks; ++i)
            {
                if(m_callbacks[i].m_mouseCallback)
                    m_callbacks[i].m_mouseCallback(mx, my, kMouseRight, _id == WM_RBUTTONDOWN);
            }   
        }
        break;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
        {
            m_keyStatus[_wparam] = (_id == WM_KEYDOWN || _id == WM_SYSKEYDOWN);
            for (int i=0; i<m_numCallbacks; ++i)
            {
                if(m_callbacks[i].m_keyCallback)
                    m_callbacks[i].m_keyCallback(_wparam, _id == WM_KEYDOWN || _id == WM_SYSKEYDOWN);
            }
        }
        break;

    default:
        break;
    }

    return DefWindowProc(_hwnd, _id, _wparam, _lparam);
}

int Win32Context::registerCallback( Win32InputCallback cb )
{
    int ret = m_numCallbacks;
    m_callbacks[m_numCallbacks++] = cb;
    return ret;
}

void Win32Context::unregisterCallback( int index )
{
    --m_numCallbacks;
    m_callbacks[index] = m_callbacks[m_numCallbacks];
}
