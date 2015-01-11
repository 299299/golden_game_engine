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
#include "config.h"

#define  DEPTH_LINE_RENDER_STATE (BGFX_STATE_RGB_WRITE  | BGFX_STATE_PT_LINES | BGFX_STATE_DEPTH_WRITE| BGFX_STATE_DEPTH_TEST_LESS| BGFX_STATE_CULL_CCW)
//#define  NO_DEPTH_LINE_RENDER_STATE (BGFX_STATE_RGB_WRITE | BGFX_STATE_PT_LINES | BGFX_STATE_DEPTH_WRITE | BGFX_STATE_DEPTH_TEST_ALWAYS | BGFX_STATE_CULL_CCW)
#define  NO_DEPTH_LINE_RENDER_STATE (BGFX_STATE_RGB_WRITE | BGFX_STATE_PT_LINES | BGFX_STATE_CULL_CCW)

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

static DebugLine              m_lines[2][MAX_DEBUG_LINES];
static DebugText              m_texts[MAX_DEBUG_TEXTS];

void DebugDrawManager::init()
{
    PosColorVertex::init();
    m_numLines[0] = m_numLines[1] = 0;
    m_numTexts = 0;
}

void DebugDrawManager::ready()
{
    m_ready = true;
    m_shader = find_shader("debug")->m_handle;
}

void DebugDrawManager::frame_start()
{
    m_numLines[0] = m_numLines[1] = 0;
    m_numTexts = 0;
}

void DebugDrawManager::draw()
{
    PROFILE(Debug_Draw);
    if(!m_ready) return;

    draw(m_numLines[0], m_lines[0], true);
    draw(m_numLines[1], m_lines[1], false);

    uint32_t num = m_numTexts;
    const DebugText* head = m_texts;

    for (uint32_t i = 0; i < num; ++i)
    {
        const DebugText& text = head[i];
        imguiDrawText((int)text.m_screenPos[0], 
                      (int)text.m_screenPos[1], 
                      ImguiTextAlign::Center, 
                      text.m_text, 
                      text.m_color);
    }
}

void DebugDrawManager::draw( uint32_t lineNum, DebugLine* lines, bool bDepth)
{
    if(!lineNum) return;
    bgfx::TransientVertexBuffer tvb;
    uint32_t numVertices = lineNum*2;
    if (!bgfx::checkAvailTransientVertexBuffer(numVertices, PosColorVertex::ms_decl))
    {
        LOGE(__FUNCTION__" checkAvailTransientVertexBuffer failed.");
        return;
    }

    bgfx::allocTransientVertexBuffer(&tvb, numVertices, PosColorVertex::ms_decl);
    PosColorVertex* vertices = (PosColorVertex*)tvb.data;
    for (uint32_t i=0; i<lineNum; ++i)
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

    bgfx::setProgram(m_shader);
    bgfx::setState(bDepth ? DEPTH_LINE_RENDER_STATE : NO_DEPTH_LINE_RENDER_STATE);
    bgfx::setVertexBuffer(&tvb, 0, numVertices);
    bgfx::submit(kDebugDrawViewId);
}

void DebugDrawManager::add_line( const float* start, const float* end, uint32_t color, bool bDepth)
{
    int index = bDepth ? 0 : 1;
    uint32_t& numLines = m_numLines[index];
    if(numLines >= (MAX_DEBUG_LINES - 1))
    {
        LOGE("%s lines num overflow!", bDepth ? "depth" : "non-depth");
        return;
    }
    DebugLine* line = m_lines[index] + numLines++;
    bx::vec3Move(line->m_start, start);
    bx::vec3Move(line->m_end, end);
    line->m_color = color;
}

void DebugDrawManager::add_aabb( const float* min, const float* max, uint32_t color, bool bDepth)
{
    float start[3], end[3];
    //1.
    vec3_make(start, min[0], min[1], min[2]);
    vec3_make(end, max[0], min[1], min[2]);
    add_line(start, end, color, bDepth);
    //2.
    vec3_make(start, max[0], min[1], min[2]);
    vec3_make(end, max[0], max[1], min[2]);
    add_line(start, end, color, bDepth);
    //3.
    vec3_make(start, max[0], max[1], min[2]);
    vec3_make(end, min[0], max[1], min[2]);
    add_line(start, end, color, bDepth);
    //4.
    vec3_make(start, min[0], max[1], min[2]);
    vec3_make(end, min[0], min[1], min[2]);
    add_line(start, end, color, bDepth);
    //5.
    vec3_make(start, min[0], min[1], min[2]);
    vec3_make(end, min[0], min[1], max[2]);
    add_line(start, end, color, bDepth);
    //6.
    vec3_make(start, max[0], min[1], min[2]);
    vec3_make(end, max[0], min[1], max[2]);
    add_line(start, end, color, bDepth);
    //7.
    vec3_make(start, max[0], max[1], min[2]);
    vec3_make(end, max[0], max[1], max[2]);
    add_line(start, end, color, bDepth);
    //8.
    vec3_make(start, min[0], max[1], min[2]);
    vec3_make(end, min[0], max[1], max[2]);
    add_line(start, end, color, bDepth);
    //9.
    vec3_make(start, min[0], min[1], max[2]);
    vec3_make(end, max[0], min[1], max[2]);
    add_line(start, end, color, bDepth);
    //9.
    vec3_make(start, max[0], min[1], max[2]);
    vec3_make(end, max[0], max[1], max[2]);
    add_line(start, end, color, bDepth);
    //10.
    vec3_make(start, max[0], max[1], max[2]);
    vec3_make(end, min[0], max[1], max[2]);
    add_line(start, end, color, bDepth);
    //11.
    vec3_make(start, min[0], max[1], max[2]);
    vec3_make(end, min[0], min[1], max[2]);
    add_line(start, end, color, bDepth);
}

void DebugDrawManager::add_axis( const hkQsTransform& t, float size , bool bDepth)
{
    const hkVector4& start_pos = t.m_translation;
    hkVector4 x_end;
    x_end.setTransformedPos(t, hkVector4(size,0,0));
    hkVector4 y_end;
    y_end.setTransformedPos(t, hkVector4(0,size,0));
    hkVector4 z_end;
    z_end.setTransformedPos(t, hkVector4(0,0,size));
    float pos[3]; float xPos[3]; float yPos[3]; float zPos[3];
    transform_vec3(pos, start_pos);
    transform_vec3(xPos, x_end);
    transform_vec3(yPos, y_end);
    transform_vec3(zPos, z_end);
    add_line(pos, xPos, RGBA(255,0,0,255), bDepth);
    add_line(pos, yPos, RGBA(0,255,0,255), bDepth);
    add_line(pos, zPos, RGBA(0,0,255,255), bDepth);
}

void DebugDrawManager::add_cross( const float* pos, float size, uint32_t color, bool bDepth)
{
    float halfSize = size/2.0f;
    float start[3], end[3];
    for (int i=0; i<3; ++i)
    {
        bx::vec3Move(start, pos);
        bx::vec3Move(end, pos);
        start[i] -= halfSize;
        end[i] += halfSize;
        add_line(start, end, color, bDepth);
    }
}

void DebugDrawManager::add_text_3d( const float* pos, const char* text, uint32_t color )
{
    float pos2D[2] = {0,0};
    bool bFlag = g_camera.project_3d_to_2d(pos2D, pos);
    if(!bFlag) return;
    DebugText& dbgText = m_texts[m_numTexts++];
    dbgText.m_color = color;
    dbgText.m_screenPos[0] = pos2D[0];
    dbgText.m_screenPos[1] = pos2D[1];
    uint32_t textLen = strlen(text);
    dbgText.m_text = FRAME_ALLOC(char, textLen+1);
    memcpy(dbgText.m_text, text, textLen);
    dbgText.m_text[textLen] = '\0';
}

void DebugDrawManager::add_sphere( const float* center, float radius, uint32_t color, bool bDepth)
{
    const uint32_t deg_step = 15;
    float tmp1[3], tmp2[3];

    for (uint32_t deg = 0; deg < 360; deg += deg_step)
    {
        const float rad0 = (float) deg * HK_REAL_DEG_TO_RAD;
        const float rad1 = ((float) deg + deg_step) * HK_REAL_DEG_TO_RAD;

        // XZ plane
        const float start0[] = {cosf(rad0) * radius, 0, -sinf(rad0) * radius};
        const float end0[] =  {cosf(rad1) * radius, 0, -sinf(rad1) * radius};
        bx::vec3Add(tmp1, start0, center);
        bx::vec3Add(tmp2, end0, center);
        add_line(tmp1, tmp2, color, bDepth);

        // XY plane
        const float start1[] = {cosf(rad0) * radius, sinf(rad0) * radius, 0};
        const float end1[] =  {cosf(rad1) * radius, sinf(rad1) * radius, 0};
        bx::vec3Add(tmp1, start1, center);
        bx::vec3Add(tmp2, end1, center);
        add_line(tmp1, tmp2, color, bDepth);

        // YZ plane
        const float start2[] = {0, sinf(rad0) * radius, -cosf(rad0) * radius};
        const float end2[] =  {0, sinf(rad1) * radius, -cosf(rad1) * radius};
        bx::vec3Add(tmp1, start2, center);
        bx::vec3Add(tmp2, end2, center);
        add_line(tmp1, tmp2, color, bDepth);
    }
}

void DebugDrawManager::add_cycle( const float* pos, const float* d, float r, uint32_t color, bool bDepth)
{
    hkQuaternion	orientation;
    hkVector4		normal;
    transform_vec3(normal, d);
    hkVector4       o;
    transform_vec3(o, pos);
    const int		steps=64;
    normal.normalize3();
    hkQuaternionUtil::_computeShortestRotation(hkVector4(0,0,1,0),normal, orientation);
    hkVector4		p;
    p.setRotatedDir(orientation,hkVector4(r,0,0,0));
    p.add4(o);
        
    float start[3], end[3];
    for(int i=1;i<=steps;++i)
    {
        const hkReal	angle=i/(hkReal)steps*HK_REAL_PI*2;
        hkVector4		v(0,0,0,0);
        v(0)	=	r*hkMath::cos(angle);
        v(1)	=	r*hkMath::sin(angle);
        hkVector4		c;
        c.setRotatedDir(orientation,v);
        c.add4(o);
        transform_vec3(start, p);
        transform_vec3(end, c);
        add_line(start, end, color, bDepth);
        p=c;
    }

    p.setAddMul4(o, normal, r/4.0f);
    transform_vec3(start, p);
    add_line(pos, start, color, bDepth);
}

void DebugDrawManager::add_triangle( const float* v0, const float* v1, const float* v2, uint32_t color, bool bDepth)
{
    add_line(v0, v1, color, bDepth);
    add_line(v1, v2, color, bDepth);
    add_line(v2, v0, color, bDepth);
}

void DebugDrawManager::add_quad(const float* center, float width, float height, uint32_t color, bool bDepth)
{
    float x = center[0];
    float y = center[1];
    float z = center[2];
    float v0[] = { x-width/2, y, z-height/2};
    float v1[] = { x+width/2, y, z-height/2};
    float v2[] = { x+width/2, y, z+height/2};
    float v3[] = { x-width/2, y, z+height/2};
    add_line(v0, v1, color, bDepth);
    add_line(v1, v2, color, bDepth);
    add_line(v2, v3, color, bDepth);
    add_line(v3, v0, color, bDepth);
}

void DebugDrawManager::add_frustum( const Frustum& frustum, uint32_t color, bool bDepth)
{
    const Vec3* vertices = frustum.m_corners;
    add_line(vertices[0].m_vec, vertices[1].m_vec, color, bDepth);
    add_line(vertices[1].m_vec, vertices[2].m_vec, color, bDepth);
    add_line(vertices[2].m_vec, vertices[3].m_vec, color, bDepth);
    add_line(vertices[3].m_vec, vertices[0].m_vec, color, bDepth);
    add_line(vertices[4].m_vec, vertices[5].m_vec, color, bDepth);
    add_line(vertices[5].m_vec, vertices[6].m_vec, color, bDepth);
    add_line(vertices[6].m_vec, vertices[7].m_vec, color, bDepth);
    add_line(vertices[7].m_vec, vertices[4].m_vec, color, bDepth);
    add_line(vertices[0].m_vec, vertices[4].m_vec, color, bDepth);
    add_line(vertices[1].m_vec, vertices[5].m_vec, color, bDepth);
    add_line(vertices[2].m_vec, vertices[6].m_vec, color, bDepth);
    add_line(vertices[3].m_vec, vertices[7].m_vec, color, bDepth);
}

void DebugDrawManager::add_grid( int gridsNum, float gridWidth, uint32_t color, bool bDepth )
{
    float start = -gridsNum * gridWidth * 0.5f;
    float startPt[3], endPt[3];

    for( int x = 0; x < gridsNum; ++x )
    {
        for( int z = 0; z < gridsNum; ++z )
        {
            vec3_make(startPt, start+x*gridWidth, 0, start+z*gridWidth );
            vec3_make(endPt, start+(x+1)*gridWidth, 0, start+z*gridWidth );
            add_line(startPt, endPt, color, bDepth);

            vec3_make(startPt, start+x*gridWidth, 0, start+z*gridWidth );
            vec3_make(endPt, start+x*gridWidth, 0, start+(z+1)*gridWidth );
            add_line(startPt, endPt, color, bDepth);
        }
    }

    vec3_make( startPt, -start, 0, start );
    vec3_make( endPt, -start, 0, -start );
    add_line(startPt, endPt, color, bDepth);

    vec3_make( startPt, start, 0, -start );
    vec3_make( endPt, -start, 0, -start );
    add_line(startPt, endPt, color, bDepth);
}

void DebugDrawManager::add_direction( const hkQsTransform& t, float len, uint32_t color, bool bDepth )
{
	float triangle_len = len;
	float quad_width = triangle_len/2, quad_height = quad_width*4;
	hkVector4 v0, v1, v2, v3;
	hkVector4 t_v0, t_v1, t_v2, t_v3;
	float s_v0[3], s_v1[3], s_v2[3], s_v3[3];

	float z_offset = (quad_height + triangle_len)/2 - triangle_len;
	v0.set(triangle_len, 0, z_offset);
	v1.set(0, 0, triangle_len + z_offset);
	v2.set(-triangle_len, 0, z_offset);

	t_v0.setTransformedPos(t, v0);
	t_v1.setTransformedPos(t, v1);
	t_v2.setTransformedPos(t, v2);

	transform_vec3(s_v0, t_v0);
	transform_vec3(s_v1, t_v1);
	transform_vec3(s_v2, t_v2);
	add_triangle(s_v0, s_v1, s_v2, color, bDepth);

	v0.set(-quad_width, 0, z_offset);
	v1.set(quad_width, 0, z_offset);
	v2.set(quad_width, 0, -quad_height + z_offset);
	v3.set(-quad_width, 0, -quad_height + z_offset);

	t_v0.setTransformedPos(t, v0);
	t_v1.setTransformedPos(t, v1);
	t_v2.setTransformedPos(t, v2);
	t_v3.setTransformedPos(t, v3);

	transform_vec3(s_v0, t_v0);
	transform_vec3(s_v1, t_v1);
	transform_vec3(s_v2, t_v2);
	transform_vec3(s_v3, t_v3);
	add_line(s_v0, s_v1, color, bDepth);
	add_line(s_v1, s_v2, color, bDepth);
	add_line(s_v2, s_v3, color, bDepth);
	add_line(s_v3, s_v0, color, bDepth);
}
