#include "Camera.h"
#include <string.h>
#include "Win32Context.h"
#include "XBoxInput.h"
#include <Common/Visualize/hkDebugDisplay.h>

Camera g_camera;
void Camera::init()
{
    memset(this, 0x00, sizeof(Camera));
    m_fov = 60.0f;
    m_near = 0.1f;
    m_far = 1000.0f;
    m_up[1] = 1.0f;
}

void Camera::update(const float* eye, const float* at)
{
    bx::vec3Move(m_eye, eye);
    bx::vec3Move(m_at, at);
    bx::mtxLookAt(m_view, eye, at);
    bx::mtxProj(m_proj, m_fov, g_win32Context.m_aspectRatio, m_near, m_far);
    m_frustum.build_view_frustum(m_view, m_proj);
}

void Camera::update(const float* transform)
{
#if 0
    float view[16];
    bx::mtxInverse(view, transform);
    bx::mtxViewFlipHandedness(m_view, view);
#else
    bx::mtxInverse(m_view, transform);
#endif
    bx::mtxProj(m_proj, m_fov, g_win32Context.m_aspectRatio, m_near, m_far);
    m_frustum.build_view_frustum(m_view, m_proj);
}

bool Camera::project_3d_to_2d(float* out2DPos, const float* in3DPos)
{
    float inp[4] = { in3DPos[0], in3DPos[1], in3DPos[2], 1 };
    float p[4];
    float pxv[16];
    bx::mtxMul(pxv, m_view, m_proj);
    bx::vec4MulMtx(p, inp, pxv);
    float w = p[3];
    if(w <= 0) return false;
    float x = p[0]/w;
    float y = -p[1]/w;
    x = (0.5f * x + 0.5f);
    y = (0.5f * y + 0.5f);
    if(x < 0.0f || x >= 1.0f) return false;
    if(y < 0.0f || y >= 1.0f) return false;
    out2DPos[0] = x * g_win32Context.m_width;
    out2DPos[1] = y * g_win32Context.m_height;
    return true;
}

void Camera::project_2d_to_3d(float* out3DPos, const float* in2DPosWithDepth)
{
    // Transform from normalized window [0, 1] to normalized device coordinates [-1, 1]
    float nwx = in2DPosWithDepth[0]/(float)g_win32Context.m_width;
    float nwy = ((float)g_win32Context.m_height-in2DPosWithDepth[1])/(float)g_win32Context.m_height;

    float cx( 2.0f * nwx - 1.0f );
    float cy( 2.0f * nwy - 1.0f );   
        
    // Create inverse view-projection matrix for unprojection
    float pxv[16];
    bx::mtxMul(pxv, m_view, m_proj);
    float invpxv[16];
    bx::mtxInverse(invpxv, pxv);

    // Unproject
    float p0[4];
    float p1[4];
    float p2[4] = {cx, cy, -1, 1};
    float p3[4] = {cx, cy, 1, 1};
    bx::vec4MulMtx(p0, p2, invpxv);
    bx::vec4MulMtx(p1, p3, invpxv);
    p0[0] /= p0[3]; p0[1] /= p0[3]; p0[2] /= p0[3];
    p1[0] /= p1[3]; p1[1] /= p1[3]; p1[2] /= p1[3];
        
    float dir[3]; 
    float normdir[3];
    bx::vec3Sub(dir, p1, p0);
    bx::vec3Norm(normdir, dir);
    bx::vec3Mul(dir, normdir, in2DPosWithDepth[2]);
    bx::vec3Add(out3DPos, m_eye, dir);
}

DebugFPSCamera::DebugFPSCamera()
:m_velocity(1.0f)
,m_rotateSpeed(0.5f)
,m_horizontalAngle(0.01f)
,m_verticalAngle(0)
{
    m_lastMouseX = g_win32Context.m_mx;
    m_lastMouseY = g_win32Context.m_my;
    m_verticalAngle = -1.0f;
}


void DebugFPSCamera::update(float dt)
{
    bool bGamePad = g_XInput.is_connected(0);
    float* eye = m_eye;
    float* at = m_at;
    float* up = g_camera.m_up;
    
    //rotate
    int32_t x = g_win32Context.m_mx;
    int32_t y = g_win32Context.m_my;
    int32_t dx = x - m_lastMouseX;
    int32_t dy = y - m_lastMouseY;
    m_lastMouseX = x;
    m_lastMouseY = y;

    if(bGamePad)
    {
        dx = g_XInput.get_ls_smooth(0)[0] * 32767.0f;
        dy = g_XInput.get_ls_smooth(0)[1] * 32767.0f;
    }

    bool bRotating = bGamePad ? true : g_win32Context.m_mouseStatus[kMouseRight];
    if(bRotating)
    {
        m_horizontalAngle += (float)dx*m_rotateSpeed*(float)dt;
        m_verticalAngle   -= (float)dy*m_rotateSpeed*(float)dt;
    }

    float direction[3] =
    {
        cosf(m_verticalAngle) * sinf(m_horizontalAngle),
        sinf(m_verticalAngle),
        cosf(m_verticalAngle) * cosf(m_horizontalAngle),
    };

    float right[3] =
    {
        sinf(m_horizontalAngle - float(M_PI)/2.0f),
        0,
        cosf(m_horizontalAngle - float(M_PI)/2.0f),
    };

    //translate
    float curVel = m_velocity * dt;
    if(GetKeyState(VK_LSHIFT) < 0)
        curVel *= 5;   // LShift

    bool bMoveFlags[4] = {false, false, false, false};
    if(bGamePad)
    {
        float lsX = g_XInput.get_ls_smooth(0)[0];
        float lsY = g_XInput.get_ls_smooth(0)[1];
        bMoveFlags[0] = lsY > 0.1f;
        bMoveFlags[1] = lsY < -0.1f;
        bMoveFlags[2] = lsX < -0.1f;
        bMoveFlags[3] = lsX > 0.1f;
    }
    else
    {
        bMoveFlags[0] = g_win32Context.m_keyStatus['W'];
        bMoveFlags[1] = g_win32Context.m_keyStatus['S'];
        bMoveFlags[2] = g_win32Context.m_keyStatus['A'];
        bMoveFlags[3] = g_win32Context.m_keyStatus['D'];
    }

    bool bMove = false;
    if(bMoveFlags[0])
    {
        float tmpRhs[3];
        float tmpPos[3];
        memcpy(tmpPos, eye, sizeof(float)*3);
        bx::vec3Mul(tmpRhs, direction, curVel);
        bx::vec3Add(eye, tmpPos, tmpRhs);
        bMove = true;
    }

    if(bMoveFlags[1])
    {
        float tmpRhs[3];
        float tmpPos[3];
        memcpy(tmpPos, eye, sizeof(float)*3);
        bx::vec3Mul(tmpRhs, direction, curVel);
        bx::vec3Sub(eye, tmpPos, tmpRhs);
        bMove = true;
    }

    if(bMoveFlags[2])
    {
        float tmpRhs[3];
        float tmpPos[3];
        memcpy(tmpPos, eye, sizeof(float)*3);
        bx::vec3Mul(tmpRhs, right, curVel);
        bx::vec3Add(eye, tmpPos, tmpRhs);
        bMove = true;
    }

    if(bMoveFlags[3])
    {
        float tmpRhs[3];
        float tmpPos[3];
        memcpy(tmpPos, eye, sizeof(float)*3);
        bx::vec3Mul(tmpRhs, right, curVel);
        bx::vec3Sub(eye, tmpPos, tmpRhs);
        bMove = true;
    }

    if(!bMove && !bRotating) 
        return;
    bx::vec3Add(at, eye, direction);
    bx::vec3Cross(up, right, direction);
    sync();
}

void DebugFPSCamera::sync()
{
    g_camera.update(m_eye, m_at);
}

DebugFPSCamera  g_fpsCamera;
void debug_update_vdb_camera(const char* name)
{
    hkVector4 from, to, up;
    transform_vec3(from, g_camera.m_eye);
    transform_vec3(to, g_camera.m_at);
    transform_vec3(to, g_camera.m_up);
    HK_DISPLAY_STAR(from, 0.25f, hkColor::BLUE);
    HK_UPDATE_CAMERA(from, to, up, g_camera.m_near, g_camera.m_far, g_camera.m_fov, name);
}


