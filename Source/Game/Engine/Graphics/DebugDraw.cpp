#include "DebugDraw.h"
#include "DataDef.h"
#include "MemorySystem.h"
#include "Resource.h"
#include "Profiler.h"
#include "MathDefs.h"
#include "Log.h"
#include "Shader.h"
#include "Graphics.h"
#include "RenderCamera.h"
#include <imgui/imgui.h>
#include <bx/fpumath.h>
#include "GameConfig.h"

#define  DEPTH_LINE_RENDER_STATE (BGFX_STATE_RGB_WRITE  | BGFX_STATE_PT_LINES | BGFX_STATE_DEPTH_WRITE| BGFX_STATE_DEPTH_TEST_LESS| BGFX_STATE_CULL_CCW)
//#define  NO_DEPTH_LINE_RENDER_STATE (BGFX_STATE_RGB_WRITE | BGFX_STATE_PT_LINES | BGFX_STATE_DEPTH_WRITE | BGFX_STATE_DEPTH_TEST_ALWAYS | BGFX_STATE_CULL_CCW)
#define  NO_DEPTH_LINE_RENDER_STATE (BGFX_STATE_RGB_WRITE | BGFX_STATE_PT_LINES | BGFX_STATE_CULL_CCW)

struct DebugLine
{
    float           m_start[3];
    float           m_end[3];
    uint32_t        m_color;
};

struct PosColorVertex
{
    float m_pos[3];
    uint32_t m_abgr;
    static void init()
    {
        ms_decl
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
            .end();
    };
    static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl PosColorVertex::ms_decl;
DebugDrawManager g_debugDrawMgr;

void DebugDrawManager::init()
{
    PosColorVertex::init();
    m_numLines[0] = m_numLines[1] = 0;
    m_lines[0] = DEBUG_ALLOC(DebugLine, MAX_DEBUG_LINES);
    m_lines[1] = DEBUG_ALLOC(DebugLine, MAX_DEBUG_LINES);
}

void DebugDrawManager::shutdown()
{

}

void DebugDrawManager::ready()
{
    m_ready = true;
    m_shader = FIND_RESOURCE(ShaderProgram, EngineTypes::PROGRAM, stringid_caculate(PROGRAM_PATH"debug"));
}

void DebugDrawManager::frame_start()
{
    m_numLines[0] = m_numLines[1] = 0;
    m_text_y = 0;
}

void DebugDrawManager::draw()
{
    PROFILE(Debug_Draw);
    if(!m_ready)
        return;

    draw(m_numLines[0], m_lines[0], true);
    draw(m_numLines[1], m_lines[1], false);
}

void DebugDrawManager::draw(int lineNum, DebugLine* lines, bool bDepth)
{
    if(!lineNum)
        return;

    if (!bgfx::isValid(m_shader->m_handle))
        return;

    bgfx::TransientVertexBuffer tvb;
    uint32_t numVertices = lineNum*2;
    if (!bgfx::checkAvailTransientVertexBuffer(numVertices, PosColorVertex::ms_decl))
    {
        LOGE("%s checkAvailTransientVertexBuffer failed.", BX_FUNCTION);
        return;
    }

    bgfx::allocTransientVertexBuffer(&tvb, numVertices, PosColorVertex::ms_decl);
    PosColorVertex* vertices = (PosColorVertex*)tvb.data;
    for (int i=0; i<lineNum; ++i)
    {
        const DebugLine& line = lines[i];
        PosColorVertex& va = vertices[i*2];
        PosColorVertex& vb = vertices[i*2+1];
        va.m_pos[0] = line.m_start[0];
        va.m_pos[1] = line.m_start[1];
        va.m_pos[2] = line.m_start[2];
        vb.m_pos[0] = line.m_end[0];
        vb.m_pos[1] = line.m_end[1];
        vb.m_pos[2] = line.m_end[2];
        va.m_abgr = vb.m_abgr = line.m_color;
    }

    bgfx::setState(bDepth ? DEPTH_LINE_RENDER_STATE : NO_DEPTH_LINE_RENDER_STATE);
    bgfx::setVertexBuffer(&tvb, 0, numVertices);
    bgfx::submit(kDebugDrawViewId, m_shader->m_handle);
}

void DebugDrawManager::add_line( const hkVector4& start, const hkVector4& end, uint32_t color, bool bDepth)
{
    int index = bDepth ? 0 : 1;
    int& numLines = m_numLines[index];
    if(numLines >= (MAX_DEBUG_LINES - 1))
    {
        LOGE("%s lines num overflow!", bDepth ? "depth" : "non-depth");
        return;
    }
    DebugLine* line = m_lines[index] + numLines++;
    transform_vec3(line->m_start, start);
    transform_vec3(line->m_end, end);
    line->m_color = color;
}

void DebugDrawManager::add_aabb( const hkVector4& min, const hkVector4& max, uint32_t color, bool bDepth)
{
    hkVector4 start, end;
    //1.
    start.set(min.getSimdAt(0), min.getSimdAt(1), min.getSimdAt(2));
    end.set(max.getSimdAt(0), min.getSimdAt(1), min.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //2.
    start.set(max.getSimdAt(0), min.getSimdAt(1), min.getSimdAt(2));
    end.set(max.getSimdAt(0), max.getSimdAt(1), min.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //3.
    start.set(max.getSimdAt(0), max.getSimdAt(1), min.getSimdAt(2));
    end.set(min.getSimdAt(0), max.getSimdAt(1), min.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //4.
    start.set(min.getSimdAt(0), max.getSimdAt(1), min.getSimdAt(2));
    end.set(min.getSimdAt(0), min.getSimdAt(1), min.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //5.
    start.set(min.getSimdAt(0), min.getSimdAt(1), min.getSimdAt(2));
    end.set(min.getSimdAt(0), min.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //6.
    start.set(max.getSimdAt(0), min.getSimdAt(1), min.getSimdAt(2));
    end.set(max.getSimdAt(0), min.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //7.
    start.set(max.getSimdAt(0), max.getSimdAt(1), min.getSimdAt(2));
    end.set(max.getSimdAt(0), max.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //8.
    start.set(min.getSimdAt(0), max.getSimdAt(1), min.getSimdAt(2));
    end.set(min.getSimdAt(0), max.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //9.
    start.set(min.getSimdAt(0), min.getSimdAt(1), max.getSimdAt(2));
    end.set(max.getSimdAt(0), min.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //10.
    start.set(max.getSimdAt(0), min.getSimdAt(1), max.getSimdAt(2));
    end.set(max.getSimdAt(0), max.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //11.
    start.set(max.getSimdAt(0), max.getSimdAt(1), max.getSimdAt(2));
    end.set(min.getSimdAt(0), max.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
    //12.
    start.set(min.getSimdAt(0), max.getSimdAt(1), max.getSimdAt(2));
    end.set(min.getSimdAt(0), min.getSimdAt(1), max.getSimdAt(2));
    add_line(start, end, color, bDepth);
}

void DebugDrawManager::add_axis( const hkQsTransform& t, float size , bool bDepth)
{
#ifdef HAVOK_COMPILE
    const hkVector4& start_pos = t.m_translation;
    hkVector4 x_end;
    x_end.setTransformedPos(t, hkVector4(size,0,0));
    hkVector4 y_end;
    y_end.setTransformedPos(t, hkVector4(0,size,0));
    hkVector4 z_end;
    z_end.setTransformedPos(t, hkVector4(0,0,size));
    add_line(start_pos, x_end, RGBA(255,0,0,255), bDepth);
    add_line(start_pos, y_end, RGBA(0,255,0,255), bDepth);
    add_line(start_pos, z_end, RGBA(0,0,255,255), bDepth);
#endif
}

void DebugDrawManager::add_cross( const hkVector4& pos, float size, uint32_t color, bool bDepth)
{
    float halfSize = size/2.0f;
    hkVector4 start, end;
    for (int i=0; i<3; ++i)
    {
        start = pos;
        end = pos;
        start(i) -= halfSize;
        end(i) += halfSize;
        add_line(start, end, color, bDepth);
    }
}

void DebugDrawManager::add_text_3d( const hkVector4& pos, uint32_t color, const char* fmt,  ...)
{
    float pos2D[2] = {0,0};
    float pos3D[3];
    transform_vec3(pos3D, pos);
    bool bFlag = g_camera.project_3d_to_2d(pos2D, pos3D);
    if(!bFlag)
        return;
    char c_buffer[2048];
    va_list argp;
    va_start(argp, fmt);
    vsnprintf(c_buffer, sizeof(c_buffer), fmt, argp);
    va_end(argp);
    imguiDrawText((int)pos2D[0], (int)pos2D[1], ImguiTextAlign::Left, c_buffer, color);
}

void DebugDrawManager::add_text_2d( const float* pos, uint32_t color, const char* fmt,  ...)
{
    char c_buffer[2048];
    va_list argp;
    va_start(argp, fmt);
    vsnprintf(c_buffer, sizeof(c_buffer), fmt, argp);
    va_end(argp);
    imguiDrawText((int)pos[0], (int)pos[1], ImguiTextAlign::Left, c_buffer, color);
}

void DebugDrawManager::add_text(uint32_t color, const char* fmt, ...)
{
    char c_buffer[2048];
    va_list argp;
    va_start(argp, fmt);
    vsnprintf(c_buffer, sizeof(c_buffer), fmt, argp);
    va_end(argp);
    const int x = 5;
    m_text_y += 20;
    imguiDrawText(x, m_text_y, ImguiTextAlign::Left, c_buffer, color);
}

void DebugDrawManager::add_sphere( const hkVector4& center, float radius, uint32_t color, bool bDepth)
{
    const uint32_t deg_step = 15;
    hkVector4 tmp1, tmp2;
    hkVector4 start, end;

    for (uint32_t deg = 0; deg < 360; deg += deg_step)
    {
        float _rad0 = bx::toRad((float)deg);
        float _rad1 = bx::toRad((float)(deg + deg_step));

        // XZ plane
        start.set(cosf(_rad0) * radius, 0, -sinf(_rad0) * radius);
        end.set(cosf(_rad1) * radius, 0, -sinf(_rad1) * radius);
        tmp1.setAdd(start, center);
        tmp2.setAdd(end, center);
        add_line(tmp1, tmp2, color, bDepth);

        // XY plane
        start.set(cosf(_rad0) * radius, sinf(_rad0) * radius, 0);
        end.set(cosf(_rad1) * radius, sinf(_rad1) * radius, 0);
        tmp1.setAdd(start, center);
        tmp2.setAdd(end, center);
        add_line(tmp1, tmp2, color, bDepth);

        // YZ plane
        start.set(0, sinf(_rad0) * radius, -cosf(_rad0) * radius);
        end.set(0, sinf(_rad1) * radius, -cosf(_rad1) * radius);
        tmp1.setAdd(start, center);
        tmp2.setAdd(end, center);
        add_line(tmp1, tmp2, color, bDepth);
    }
}

void DebugDrawManager::add_cycle( const hkVector4& pos, const hkVector4& d, float r, uint32_t color, bool bDepth)
{
#ifdef HAVOK_COMPILE
    hkQuaternion    orientation;
    hkVector4       normal = d;
    const int       steps=64;
    normal.normalize3();
    hkQuaternionUtil::_computeShortestRotation(hkVector4(0,0,1,0),normal, orientation);
    hkVector4       p;
    p.setRotatedDir(orientation,hkVector4(r,0,0,0));
    p.add4(pos);

    for(int i=1;i<=steps;++i)
    {
        const hkReal    angle=i/(hkReal)steps*HK_REAL_PI*2;
        hkVector4       v(0,0,0,0);
        v(0)    =   r*hkMath::cos(angle);
        v(1)    =   r*hkMath::sin(angle);
        hkVector4       c;
        c.setRotatedDir(orientation,v);
        c.add4(pos);
        add_line(p, c, color, bDepth);
        p=c;
    }

    p.setAddMul4(pos, normal, r/4.0f);
    add_line(pos, p, color, bDepth);
#endif
}

void DebugDrawManager::add_triangle( const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, uint32_t color, bool bDepth)
{
    add_line(v0, v1, color, bDepth);
    add_line(v1, v2, color, bDepth);
    add_line(v2, v0, color, bDepth);
}

void DebugDrawManager::add_quad(const hkVector4& center, float width, float height, uint32_t color, bool bDepth)
{
    float x = center.getSimdAt(0);
    float y = center.getSimdAt(1);
    float z = center.getSimdAt(2);
    hkVector4 v0, v1, v2, v3;
    v0.set(x-width/2, y, z-height/2);
    v1.set(x+width/2, y, z-height/2);
    v2.set(x+width/2, y, z+height/2);
    v3.set(x-width/2, y, z+height/2);
    add_line(v0, v1, color, bDepth);
    add_line(v1, v2, color, bDepth);
    add_line(v2, v3, color, bDepth);
    add_line(v3, v0, color, bDepth);
}

void DebugDrawManager::add_frustum( const Frustum& frustum, uint32_t color, bool bDepth)
{
    const Vec3* vertices = frustum.m_corners;
    hkVector4 start, end;

    transform_vec3(start, vertices[0].m_vec);
    transform_vec3(end, vertices[1].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[1].m_vec);
    transform_vec3(end, vertices[2].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[2].m_vec);
    transform_vec3(end, vertices[3].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[3].m_vec);
    transform_vec3(end, vertices[0].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[4].m_vec);
    transform_vec3(end, vertices[5].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[5].m_vec);
    transform_vec3(end, vertices[6].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[6].m_vec);
    transform_vec3(end, vertices[7].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[7].m_vec);
    transform_vec3(end, vertices[4].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[0].m_vec);
    transform_vec3(end, vertices[4].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[1].m_vec);
    transform_vec3(end, vertices[5].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[2].m_vec);
    transform_vec3(end, vertices[6].m_vec);
    add_line(start, end, color, bDepth);

    transform_vec3(start, vertices[3].m_vec);
    transform_vec3(end, vertices[7].m_vec);
    add_line(start, end, color, bDepth);
}

void DebugDrawManager::add_grid( int gridsNum, float gridWidth, uint32_t color, bool bDepth )
{
    float start = -gridsNum * gridWidth * 0.5f;
    hkVector4 startPt, endPt;

    for (int i = 0; i<=gridsNum; ++i)
    {
        startPt.set(start + gridWidth * i, 0, start);
        endPt.set(start + gridWidth * i, 0, start + gridWidth * gridsNum);
        add_line(startPt, endPt, color, bDepth);
    }

    for (int i = 0; i<=gridsNum; ++i)
    {
        startPt.set(start, 0, start + gridWidth * i);
        endPt.set(start + gridWidth * gridsNum, 0, start + gridWidth * i);
        add_line(startPt, endPt, color, bDepth);
    }
}

