#pragma once
#include "Prerequisites.h"
#include <bgfx.h>

struct Frustum;
struct DebugLine;
struct DebugText;
struct ShaderProgram;

struct DebugDrawManager
{
    void init();
    void shutdown();

    //must called when common package loaded.
    void ready();
    void draw();
    void frame_start();
    void add_line(const hkVector4& start, const hkVector4& end, uint32_t color, bool bDepth);
    void add_aabb(const hkVector4& min, const hkVector4& max, uint32_t color, bool bDepth);
    void add_axis(const hkQsTransform& t, float size = 0.25f, bool bDepth = false);
    void add_cross(const hkVector4& pos, float size, uint32_t color, bool bDepth);
    void add_text_3d(const hkVector4& pos, uint32_t color, const char* fmt, ...);
    void add_text_2d(const float* pos, uint32_t color, const char* fmt, ...);
    void add_text(uint32_t color, const char* fmt, ...);

    void add_sphere(const hkVector4& pos, float radius, uint32_t color, bool bDepth);
    void add_cycle(const hkVector4& pos, const hkVector4& normal, float raidus, uint32_t color, bool bDepth);
    void add_triangle(const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, uint32_t color, bool bDepth);
    void add_quad(const hkVector4& center, float width, float height, uint32_t color, bool bDepth);
    void add_frustum(const Frustum& frustum, uint32_t color, bool bDepth);
    void add_grid(int gridsNum, float gridWidth, uint32_t color, bool bDepth);

    DebugLine*              m_lines[2];
    int                     m_numLines[2];

    int                     m_text_y;

    ShaderProgram*          m_shader;
    bool                    m_ready;

private:
    void draw(int lineNum, DebugLine* lines, bool bDepth);
};

extern DebugDrawManager g_debugDrawMgr;