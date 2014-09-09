#pragma once
#include "Prerequisites.h"
#include "MathDefs.h"

struct Camera
{
    float                       m_view[16];
    float                       m_proj[16];
    Frustum                     m_frustum;
    float                       m_up[3];
    float                       m_eye[3];
    float                       m_at[3];

    float                       m_fov;
    float                       m_near;
    float                       m_far;

    void init();
    void update(const float* eye, const float* at);
    void update(const float* transform);
    bool project3DPosTo2D(float* out2DPos, const float* in3DPos);
    void project2DPosTo3D(float* out3DPos, const float* in2DPosWithDepth);
};

extern Camera g_camera;

struct DebugFPSCamera
{
    float                      m_eye[3];
    float                      m_at[3];
    float                      m_velocity;
    float                      m_rotateSpeed;
    int32_t                    m_lastMouseX;
    int32_t                    m_lastMouseY;
    float                      m_horizontalAngle;
    float                      m_verticalAngle;

    DebugFPSCamera();
    void update(float dt);
    void sync();
};
void debug_update_vdb_camera(const char* name = "user-camera");