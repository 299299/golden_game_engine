#pragma once
#include "Prerequisites.h"
#include <bgfx.h>

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
    void frameStart();
    void addLine(const float* start, const float* end, uint32_t color, bool bDepth);
    void addAabb(const float* min, const float* max, uint32_t color, bool bDepth);
    void addAxis(const hkQsTransform& t, float size = 0.25f, bool bDepth = false);
    void addCross(const float* pos, float size, uint32_t color, bool bDepth);
    void add3DText(const char* text, const float* pos, uint32_t color);
    void addSphere(const float* pos, float radius, uint32_t color, bool bDepth);
    void addCircle(const float* pos, const float* normal, float raidus, uint32_t color, bool bDepth);
    void addTriangle(const float* v0, const float* v1, const float* v2, uint32_t color, bool bDepth);
    void addFrustum(const Frustum& frustum, uint32_t color, bool bDepth);
    void addGrid(int gridsNum, float gridWidth, uint32_t color, bool bDepth);

    DebugLine*              m_lines[2];
    uint32_t                m_numLines[2];
    DebugText*              m_texts;
    uint32_t                m_numTexts;

    bgfx::ProgramHandle     m_shader;
    bool                    m_ready;

private:
    void draw(uint32_t lineNum, DebugLine* lines, bool bDepth);
};

extern DebugDrawManager g_debugDrawMgr;