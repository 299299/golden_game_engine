#pragma once
#include "Prerequisites.h"
#include <bgfx/bgfx.h>

struct Frustum;

struct DebugLine
{
    float           m_start[3];
    float           m_end[3];
    uint32_t        m_color;
};

struct DebugText
{
    float           m_screenPos[2];
    uint32_t        m_color;
    char*           m_text;
};

struct DebugDrawManager
{
    void init();
    //must called when common package loaded.
    void ready();
    void draw();
    void frame_start();
    void add_line(const float* start, const float* end, uint32_t color, bool bDepth);
    void add_aabb(const float* min, const float* max, uint32_t color, bool bDepth);
    void add_axis(const hkQsTransform& t, float size = 0.25f, bool bDepth = false);
    void add_cross(const float* pos, float size, uint32_t color, bool bDepth);
    void add_text_3d(const float* pos, const char* text, uint32_t color);
    void add_sphere(const float* pos, float radius, uint32_t color, bool bDepth);
    void add_cycle(const float* pos, const float* normal, float raidus, uint32_t color, bool bDepth);
    void add_triangle(const float* v0, const float* v1, const float* v2, uint32_t color, bool bDepth);
    void add_frustum(const Frustum& frustum, uint32_t color, bool bDepth);
    void add_grid(int gridsNum, float gridWidth, uint32_t color, bool bDepth);

    uint32_t                m_numLines[2];
    uint32_t                m_numTexts;

    bgfx::ProgramHandle     m_shader;
    bool                    m_ready;

private:
    void draw(uint32_t lineNum, DebugLine* lines, bool bDepth);
};

extern DebugDrawManager g_debugDrawMgr;