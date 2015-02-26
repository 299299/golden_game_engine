#include "Graphics.h"
#include "Log.h"
#include "DataDef.h"
#include "MemorySystem.h"
#include "Profiler.h"
//============================================
#include "RenderCamera.h"
#include "DebugDraw.h"
#include "ShadingEnviroment.h"
#include "Material.h"
#include "Light.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Resource.h"
#include "Win32Context.h"
#include "Utils.h"
#include "Gui.h"
#include "Component.h"
//============================================
#include <bx/fpumath.h>
#include <bgfxplatform.h>
#include <bx/bx.h>
#include <bx/allocator.h>
#include <bx/uint32_t.h>
#include <bx/string.h>


#define BGFX_COLOR 0x303030ff

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

struct bgfxCallback : public bgfx::CallbackI
{
    virtual void fatal(bgfx::Fatal::Enum _code, const char* _str) { LOGE(_str); }
    virtual uint32_t cacheReadSize(uint64_t _id) { return 0; };
    virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) { return false; }
    virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) {};
    virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip){};
    virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx::TextureFormat::Enum _format, bool _yflip) {};
    virtual void captureEnd() {};
    virtual void captureFrame(const void* _data, uint32_t _size) {};
};

struct PosTexCoord0Vertex
{
    float m_x;
    float m_y;
    float m_z;
    float m_u;
    float m_v;
    static void init()
    {
        ms_decl
            .begin()
            .add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();
    }
    static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl            PosTexCoord0Vertex::ms_decl;

//==============================================================
//      PUBLIC GLOBAL VARIABLES
//==============================================================
UniformPerFrame             g_uniformPerFrame;
UniformPerObject            g_uniformPerObject;
UniformPerLight             g_uniformLights;
ShadowMap                   g_shadowMap;
bool                        g_hdr = true;
//==============================================================
//      INNER GLOBAL VARIABLES
//==============================================================
static bgfxCallback         g_bgfxCallback;
static uint32_t             g_resetFlag = BGFX_RESET_MSAA_X4|BGFX_RESET_VSYNC;
static bgfx::UniformHandle* g_engineUniforms;
static uint32_t             g_numEngineUniforms = 0;
static FrameBuffer*         g_frameBuffers;
static uint32_t             g_numFrameBuffers = 0;

INTERNAL bgfx::UniformHandle createEngineUniform(const char* name, bgfx::UniformType::Enum type, int num = 1)
{
    if(!name){
        bgfx::UniformHandle handle = BGFX_INVALID_HANDLE;
        return handle;
    }
    ENGINE_ASSERT(g_numEngineUniforms < MAX_UNIFORM_NUM, "g_numEngineUniforms < MAX_UNIFORM_NUM");
    bgfx::UniformHandle& handle = g_engineUniforms[g_numEngineUniforms++];
    handle = bgfx::createUniform(name, type, num);
    return handle;
}

INTERNAL FrameBuffer* createFrameBuffer(int w, int h, int wDiv, int hDiv, bool scaled, uint32_t numTextures, FrameBufferTexture* textures)
{
    ENGINE_ASSERT(g_numFrameBuffers < MAX_FRAMEBUFFER_NUM, "g_numEngineUniforms < MAX_UNIFORM_NUM");
    FrameBuffer* fb = g_frameBuffers + g_numFrameBuffers;
    ++g_numFrameBuffers;
    fb->m_handle.idx = bgfx::invalidHandle;
    fb->m_numTextures = numTextures;
    fb->m_realSize[0] = w;
    fb->m_realSize[1] = h;
    fb->m_sizeDiv[0] = wDiv;
    fb->m_sizeDiv[1] = hDiv;
    fb->m_scaled = scaled;
    ENGINE_ASSERT(numTextures <= BX_COUNTOF(fb->m_texInfo), "frame buffer texture num overflow.");
    memcpy(fb->m_texInfo, textures, numTextures*sizeof(FrameBufferTexture));
    fb->create();
    return fb;
}
INTERNAL FrameBuffer* createFrameBuffer(int w, int h, int wDiv, int hDiv, bool scaled,
                               bgfx::TextureFormat::Enum format,
                               uint32_t texFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP)
{
    texFlags |= texFlags & BGFX_TEXTURE_RT_MSAA_MASK ? 0 : BGFX_TEXTURE_RT;
    FrameBufferTexture texInfo[1] = {{format, texFlags}};
    return createFrameBuffer(w, h, wDiv, hDiv, scaled, 1, texInfo);
}

INTERNAL void createUniforms()
{
    g_engineUniforms = COMMON_ALLOC(bgfx::UniformHandle, MAX_UNIFORM_NUM);
    extern const char*  g_textureNames[];
    g_uniformPerFrame.m_time = createEngineUniform("u_time", bgfx::UniformType::Uniform1f);
    g_uniformPerFrame.m_ambientSkyColor = createEngineUniform("u_ambientSkyColor", bgfx::UniformType::Uniform3fv);
    g_uniformPerFrame.m_ambientGroundColor = createEngineUniform("u_ambientGroundColor", bgfx::UniformType::Uniform3fv);
    g_uniformPerFrame.m_camPos = createEngineUniform("u_camPos", bgfx::UniformType::Uniform3fv);
    g_uniformPerFrame.m_fogParams = createEngineUniform("u_fogParams", bgfx::UniformType::Uniform4fv);
    g_uniformPerFrame.m_zParams = createEngineUniform("u_camDist", bgfx::UniformType::Uniform2fv);

    g_uniformPerObject.m_uv = createEngineUniform("u_uvOffsetAndRepeat", bgfx::UniformType::Uniform4fv);
    for(int i=0; i<TEX_MAX_SLOT; ++i)
    {
        const char* _name = g_textureNames[i];
        if(!_name)
            break;
        g_uniformPerObject.m_tex[i] = createEngineUniform(_name, bgfx::UniformType::Uniform1iv);
    }

    g_uniformPerObject.m_diffuse = createEngineUniform("u_diffuseColor", bgfx::UniformType::Uniform4fv);
    g_uniformPerObject.m_specular = createEngineUniform("u_specularColor", bgfx::UniformType::Uniform4fv);
    g_uniformPerObject.m_params1 = createEngineUniform("u_matParams1", bgfx::UniformType::Uniform4fv);

    g_uniformLights.m_color = createEngineUniform("u_lightColor", bgfx::UniformType::Uniform3fv, BGFX_CONFIG_MAX_LIGHTS);
    g_uniformLights.m_info = createEngineUniform("u_lightInfo", bgfx::UniformType::Uniform4fv, BGFX_CONFIG_MAX_LIGHTS);
    g_uniformLights.m_vec = createEngineUniform("u_lightVec", bgfx::UniformType::Uniform3fv, BGFX_CONFIG_MAX_LIGHTS);
    g_uniformLights.m_type = createEngineUniform("u_lightType", bgfx::UniformType::Uniform1i, BGFX_CONFIG_MAX_LIGHTS);

    g_shadowMap.m_lightMtx = createEngineUniform("u_lightMtx", bgfx::UniformType::Uniform4x4fv);
    g_shadowMap.m_paramUniform = createEngineUniform("u_shadowParams", bgfx::UniformType::Uniform3fv);
}

void Graphics::register_factories()
{
    ResourceFactory _mesh = {0, 0, 0, bringin_resource_mesh, bringout_resource_mesh, EngineNames::MESH, 0};
    g_resourceMgr.register_factory(_mesh);

    ResourceFactory _texture = {0, 0, 0, 0, bringout_resource_texture, EngineNames::TEXTURE, 0};
    g_resourceMgr.register_factory(_texture);

    ResourceFactory _texture3d = {0, 0, 0, bringin_resource_texture3d, bringout_resource_texture3d, EngineNames::TEXTURE_3D, 0};
    g_resourceMgr.register_factory(_texture3d);

    ResourceFactory _shader = {0, 0, 0, bringin_resource_shader, bringout_resource_shader, EngineNames::SHADER, 0};
    g_resourceMgr.register_factory(_shader);

    ResourceFactory _program = {0, 0, lookup_resource_shader_program, bringin_resource_shader_program, bringout_resource_shader_program, EngineNames::PROGRAM, 1};
    g_resourceMgr.register_factory(_program);

    ResourceFactory _material = {0, 0, lookup_resource_material, bringin_resource_material, 0, EngineNames::MATERIAL, 2 };
    g_resourceMgr.register_factory(_material);

    ResourceFactory _shadingEnv = {0,0,lookup_resource_shading_enviroment,0,0,EngineNames::SHADING_ENV, 4};
    g_resourceMgr.register_factory(_shadingEnv);

    ComponentFactory _model = {create_model, destroy_model, get_model, num_all_model, get_all_model, transform_model, lookup_model_instance_data, 0};
    g_componentMgr.register_factory(_model, EngineTypes::MODEL);

    ComponentFactory _light = {create_light, destroy_light, get_light, num_all_light, get_all_light, transform_light, 0, 0};
    g_componentMgr.register_factory(_light, EngineTypes::LIGHT);
}

void Graphics::init(void* hwnd, bool bFullScreen)
{
    TIMELOG("Graphics::Init");

#ifdef HAVOK_COMPILE
    bgfx::winSetHwnd((HWND)hwnd);
#else
    hwnd = 0;
#endif

    bx::debugOutput("bgfx init started ---\n");
    bgfx::init(hwnd ? bgfx::RendererType::Direct3D11 : bgfx::RendererType::Null, &g_bgfxCallback);
    bx::debugOutput("bgfx init ended ---\n");

    const bgfx::Caps* caps = bgfx::getCaps();
    bool shadowSamplerSupported = 0 != (caps->supported & BGFX_CAPS_TEXTURE_COMPARE_LEQUAL);
    LOGD("support shadow sampler = %d", shadowSamplerSupported);

    if(bFullScreen) g_resetFlag |= BGFX_RESET_FULLSCREEN;
    bgfx::reset(g_win32Context.m_width, g_win32Context.m_height, g_resetFlag);
    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setViewClear(kShadowViewId, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, BGFX_COLOR, 1.0f, 0);
    bgfx::setViewClear(kBackgroundViewId, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, BGFX_COLOR, 1.0f, 0);

    g_frameBuffers = COMMON_ALLOC(FrameBuffer, MAX_FRAMEBUFFER_NUM);
    PosTexCoord0Vertex::init();
    createUniforms();

    g_camera.init();
    g_debugDrawMgr.init();
    g_guiMgr.init();
    g_modelWorld.init(MAX_MODELS);
    g_lightWorld.init(MAX_LIGHTS);

    //----------------------------------------------
    // view name for debug.
    extern const char* g_viewGroupNames[];
    for(int i=0; i<=kHDRBrightViewId;++i)
    {
        bgfx::setViewName(i, g_viewGroupNames[i]);
    }
    for (int i = 0; i < N_PASSES; ++i)
    {
        char buf[32];
        bx::snprintf(buf, sizeof(buf), "h-blur-%d", i+1);
        bgfx::setViewName(kHDRBlurViewIdStart + i * 2 + 0, buf);
        bx::snprintf(buf, sizeof(buf), "v-blur-%d", i+1);
        bgfx::setViewName(kHDRBlurViewIdStart + i * 2 + 1, buf);
    }
    bgfx::setViewName(kCombineViewId, "combine");
    bgfx::setViewName(kDebugDrawViewId, "debug");
    bgfx::setViewName(kGUIViewId, "gui");
}

void Graphics::ready()
{
    TIMELOG("Graphics::PostInit");
    g_debugDrawMgr.ready();
}

void Graphics::shutdown()
{
    for (uint32_t i=0;i<g_numFrameBuffers;++i)
    {
        bgfx::destroyFrameBuffer(g_frameBuffers[i].m_handle);
    }
    COMMON_DEALLOC(g_frameBuffers);
    for(uint32_t i=0; i<g_numEngineUniforms; ++i)
    {
        bgfx::destroyUniform(g_engineUniforms[i]);
    }
    COMMON_DEALLOC(g_engineUniforms);
    g_guiMgr.shutdown();
    g_modelWorld.shutdown();
    g_lightWorld.shutdown();
    bgfx::shutdown();
}

void Graphics::update(ShadingEnviroment* env, float dt)
{
    PROFILE(Graphics_Update);
    g_modelWorld.update(dt);
    g_lightWorld.update(dt);
    g_guiMgr.update(dt);

    g_modelWorld.cull_models(g_camera.m_frustum);
    if(env)
        g_lightWorld.update_shadow(
            env->m_shadow_area_size,
            env->m_shadow_far,
            g_camera.m_eye);
    if(g_lightWorld.m_shadowLight)
        g_modelWorld.cull_shadows(g_lightWorld.m_shadowFrustum);
}

INTERNAL void submitPerFrameUniforms()
{
    extern float g_totalSeconds;
    bgfx::setUniform(g_uniformPerFrame.m_time, &g_totalSeconds);
    bgfx::setUniform(g_uniformPerFrame.m_camPos, g_camera.m_eye);
    float zparams[2] = {g_camera.m_near, g_camera.m_far};
    bgfx::setUniform(g_uniformPerFrame.m_zParams, zparams);
}

void Graphics::draw(ShadingEnviroment* env)
{
    //force clear color & depth executed.
    bgfx::submit(kShadowViewId);
    bgfx::submit(kBackgroundViewId);

    g_guiMgr.draw();

    //prepare for view rects.
    int w = g_win32Context.m_width;
    int h = g_win32Context.m_height;
    bgfx::setViewRect(kBackgroundViewId, 0, 0, w, h);
    bgfx::setViewRect(kSceneViewId, 0, 0, w, h);
    bgfx::setViewRect(kDebugDrawViewId, 0, 0, w, h);
    bgfx::setViewRect(kCombineViewId, 0, 0, w, h);

    const float* view = g_camera.m_view;
    const float* proj = g_camera.m_proj;
    bgfx::setViewTransform(kBackgroundViewId, view, proj);
    bgfx::setViewTransform(kSceneViewId, view, proj);
    bgfx::setViewTransform(kDebugDrawViewId, view, proj);

    submitPerFrameUniforms();
    if(env)
    {
        g_lightWorld.submit_lights(env);
        env->submit();
    }
    g_modelWorld.submit_models();
    if(g_lightWorld.m_shadowLight) g_modelWorld.submit_shadows();
    g_debugDrawMgr.draw();
    PROFILE(bgfx_frame);
    bgfx::frame();
}

void Graphics::frame_start()
{
    g_debugDrawMgr.frame_start();
    g_guiMgr.frame_start();

    if(g_win32Context.m_sizeChanged)
    {
        int w = g_win32Context.m_width;
        int h = g_win32Context.m_height;
        bgfx::reset(w, h, g_resetFlag);
        for (uint32_t i=0; i<g_numFrameBuffers; ++i)
        {
            FrameBuffer& fb = g_frameBuffers[i];
            if(!fb.m_scaled) continue;
            fb.resize(w, h);
        }
    }
}

void Graphics::frame_end()
{
    g_guiMgr.frame_end();
}

void FrameBuffer::resize( int w, int h )
{
    if(!m_scaled) return;
    int newWidth = w/m_sizeDiv[0];
    int newHeight = h/m_sizeDiv[1];
    if(m_realSize[0] == newWidth && m_realSize[1] == newHeight) return;
    m_realSize[0] = newWidth;
    m_realSize[1] = newHeight;
    create();
}

void FrameBuffer::create()
{
    if(bgfx::isValid(m_handle)) bgfx::destroyFrameBuffer(m_handle);

    for(uint32_t i=0; i<m_numTextures; ++i)
    {
        FrameBufferTexture& texInfo = m_texInfo[i];
        m_textures[i] = bgfx::createTexture2D(m_realSize[0], m_realSize[1], 1, texInfo.m_format, texInfo.m_flag);
        ENGINE_ASSERT(bgfx::isValid(m_textures[i]), "bgfx::isValid(m_textures[i])");
    }

    m_handle = bgfx::createFrameBuffer(m_numTextures, m_textures, true);
    ENGINE_ASSERT(bgfx::isValid(m_handle), "bgfx::isValid(m_handle)");
}

void FrameBuffer::begin(uint32_t viewId)
{
    bgfx::setViewRect(viewId, 0, 0, m_realSize[0], m_realSize[1]);
    bgfx::setViewFrameBuffer(viewId, m_handle);
}

void FrameBuffer::end(uint32_t viewId)
{
    bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
    Graphics::screenspace_quad((float)m_realSize[0], (float)m_realSize[1]);
    bgfx::submit(viewId);
}

void Graphics::set_texture( int slot, bgfx::TextureHandle handle )
{
    bgfx::setTexture(slot, g_uniformPerObject.m_tex[slot], handle);
}

void Graphics::set_texture( int slot, bgfx::FrameBufferHandle handle )
{
    bgfx::setTexture(slot, g_uniformPerObject.m_tex[slot], handle);
}

void Graphics::screenspace_quad(float _textureWidth, float _textureHeight, float _width, float _height)
{
    if (!bgfx::checkAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_decl))
    {
        LOGE("%s checkAvailTransientVertexBuffer failed.", BX_FUNCTION);
        return;
    }

    bgfx::TransientVertexBuffer vb;
    bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_decl);
    PosTexCoord0Vertex* vertex = (PosTexCoord0Vertex*)vb.data;

    const float zz = 0.0f;

    const float minx = -_width;
    const float maxx =  _width;
    const float miny = 0.0f;
    const float maxy = _height*2.0f;
    const float minu = -1.0f;
    const float maxu =  1.0f;

    float minv = 0;
    float maxv = 2.0f;

    vertex[0].m_x = minx;
    vertex[0].m_y = miny;
    vertex[0].m_z = zz;
    vertex[0].m_u = minu;
    vertex[0].m_v = minv;

    vertex[1].m_x = maxx;
    vertex[1].m_y = miny;
    vertex[1].m_z = zz;
    vertex[1].m_u = maxu;
    vertex[1].m_v = minv;

    vertex[2].m_x = maxx;
    vertex[2].m_y = maxy;
    vertex[2].m_z = zz;
    vertex[2].m_u = maxu;
    vertex[2].m_v = maxv;

    bgfx::setVertexBuffer(&vb);
}

//I don`t want gl&d3d9 support, but I don`t want to modify bgfx.cpp either
//so I add this -_-
namespace bgfx
{
    struct RendererContextI* rendererCreateGL() { return 0;};
    void rendererDestroyGL() {};
    struct RendererContextI* rendererCreateD3D9()  { return 0;};
    void rendererDestroyD3D9() {};
    struct RendererContextI* rendererCreateD3D12()  { return 0;};
    void rendererDestroyD3D12() {};
};


