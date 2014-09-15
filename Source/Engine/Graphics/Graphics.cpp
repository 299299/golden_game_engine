#include "Graphics.h"
#include "Log.h"
#include "DataDef.h"
#include "MemorySystem.h"
#include "Profiler.h"
//============================================
#include "Camera.h"
#include "Scene.h"
#include "DebugDraw.h"
#include "ShadingEnviroment.h"
#include "Material.h"
#include "Light.h"
#include "Shader.h"
#include "Texture.h"
#include "Resource.h"
#include "Win32Context.h"
#include "Utils.h"
#include "Gui.h"
//============================================
#include <bx/fpumath.h>
#include <bgfxplatform.h>
#include <bx/bx.h>
#include <bx/allocator.h>
#include <bx/uint32_t.h>
#include <entry/dbg.h>


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
PostProcess                 g_postProcess;
bool                        g_hdr = true;
bool                        g_smallDebugDraw = false;
int                         g_dbgTexIndex = 0;
//==============================================================
//      INNER GLOBAL VARIABLES
//==============================================================
static bgfxCallback         g_bgfxCallback;
static uint32_t             g_resetFlag = BGFX_RESET_VSYNC|BGFX_RESET_MSAA_X4;
static bgfx::UniformHandle* g_engineUniforms;
static uint32_t             g_numEngineUniforms = 0;
static FrameBuffer*         g_frameBuffers = 0;
static uint32_t             g_numFrameBuffers = 0;
static uint64_t postprocess_state = BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE;
static int                  g_status = 0;


void postProcessInit();
void postProcessSubmit(ShadingEnviroment* env);

bgfx::UniformHandle createEngineUniform(const char* name, bgfx::UniformType::Enum type, int num = 1)
{
    if(!name){
        bgfx::UniformHandle handle = BGFX_INVALID_HANDLE;
        return handle;
    }
    HK_ASSERT(0, g_numEngineUniforms < MAX_UNIFORM_NUM);
    bgfx::UniformHandle& handle = g_engineUniforms[g_numEngineUniforms++];
    handle = bgfx::createUniform(name, type, num);
    return handle;
}

FrameBuffer* createFrameBuffer(int w, int h, int wDiv, int hDiv, bool scaled, uint32_t numTextures, FrameBufferTexture* textures)
{
    HK_ASSERT(0, g_numFrameBuffers < MAX_FRAMEBUFFER_NUM);
    FrameBuffer* fb = g_frameBuffers + g_numFrameBuffers;
    ++g_numFrameBuffers;
    fb->m_handle.idx = bgfx::invalidHandle;
    fb->m_numTextures = numTextures;
    fb->m_realSize[0] = w;
    fb->m_realSize[1] = h;
    fb->m_sizeDiv[0] = wDiv;
    fb->m_sizeDiv[1] = hDiv;
    fb->m_scaled = scaled;
    fb->m_textures = STATIC_ALLOC(bgfx::TextureHandle, numTextures);
    fb->m_texInfo = STATIC_ALLOC(FrameBufferTexture, numTextures);
    memcpy(fb->m_texInfo, textures, numTextures*sizeof(FrameBufferTexture));
    fb->create();
    return fb;
}
FrameBuffer* createFrameBuffer(int w, int h, int wDiv, int hDiv, bool scaled, 
                               bgfx::TextureFormat::Enum format, 
                               uint32_t texFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP)
{
    texFlags |= texFlags & BGFX_TEXTURE_RT_MSAA_MASK ? 0 : BGFX_TEXTURE_RT;
    FrameBufferTexture texInfo[1] = {format, texFlags};
    return createFrameBuffer(w, h, wDiv, hDiv, scaled, 1, texInfo);
}

void createUniforms()
{
    extern const char*  g_textureNames[];
    g_engineUniforms = STATIC_ALLOC(bgfx::UniformHandle, MAX_UNIFORM_NUM);
    g_frameBuffers = STATIC_ALLOC(FrameBuffer, MAX_FRAMEBUFFER_NUM);

    g_uniformPerFrame.m_time = createEngineUniform("u_time", bgfx::UniformType::Uniform1f);
    g_uniformPerFrame.m_ambientSkyColor = createEngineUniform("u_ambientSkyColor", bgfx::UniformType::Uniform3fv);
    g_uniformPerFrame.m_ambientGroundColor = createEngineUniform("u_ambientGroundColor", bgfx::UniformType::Uniform3fv);
    g_uniformPerFrame.m_camPos = createEngineUniform("u_camPos", bgfx::UniformType::Uniform3fv);
    g_uniformPerFrame.m_fogParams = createEngineUniform("u_fogParams", bgfx::UniformType::Uniform4fv);
    g_uniformPerFrame.m_zParams = createEngineUniform("u_camDist", bgfx::UniformType::Uniform2fv);

    g_uniformPerObject.m_uv = createEngineUniform("u_uvOffsetAndRepeat", bgfx::UniformType::Uniform4fv);
    for(int i=0; i<TEX_MAX_SLOT; ++i)
    {
        g_uniformPerObject.m_tex[i] = createEngineUniform(g_textureNames[i], bgfx::UniformType::Uniform1iv);
    }

    g_uniformPerObject.m_diffuse = createEngineUniform("u_diffuseColor", bgfx::UniformType::Uniform4fv);
    g_uniformPerObject.m_specular = createEngineUniform("u_specularColor", bgfx::UniformType::Uniform4fv);
    g_uniformPerObject.m_rimColorInfo = createEngineUniform("u_rimColorInfo", bgfx::UniformType::Uniform3fv);
    g_uniformPerObject.m_translucencyInfo = createEngineUniform("u_translucentInfo", bgfx::UniformType::Uniform4fv);
    g_uniformPerObject.m_skinRampOuterColor = createEngineUniform("u_skinRampOuterColor", bgfx::UniformType::Uniform3fv);
    g_uniformPerObject.m_skinRampMediumColor = createEngineUniform("u_skinRampMediumColor", bgfx::UniformType::Uniform3fv);
    g_uniformPerObject.m_skinRampInnerColor = createEngineUniform("u_skinRampInnerColor", bgfx::UniformType::Uniform3fv);
    g_uniformPerObject.m_params1 = createEngineUniform("u_matParams1", bgfx::UniformType::Uniform4fv);
    g_uniformPerObject.m_opacityParams = createEngineUniform("u_opacityParams", bgfx::UniformType::Uniform3fv);

    g_uniformLights.m_color = createEngineUniform("u_lightColor", bgfx::UniformType::Uniform3fv, BGFX_CONFIG_MAX_LIGHTS);
    g_uniformLights.m_info = createEngineUniform("u_lightInfo", bgfx::UniformType::Uniform4fv, BGFX_CONFIG_MAX_LIGHTS);
    g_uniformLights.m_vec = createEngineUniform("u_lightVec", bgfx::UniformType::Uniform3fv, BGFX_CONFIG_MAX_LIGHTS);
    g_uniformLights.m_type = createEngineUniform("u_lightType", bgfx::UniformType::Uniform1i, BGFX_CONFIG_MAX_LIGHTS);

    g_shadowMap.m_lightMtx = createEngineUniform("u_lightMtx", bgfx::UniformType::Uniform4x4fv);
    g_shadowMap.m_paramUniform = createEngineUniform("u_shadowParams", bgfx::UniformType::Uniform3fv);

    g_postProcess.m_ppUniform = createEngineUniform("u_ppParams",  bgfx::UniformType::Uniform4fv);
    g_postProcess.m_bloomUniform = createEngineUniform("u_bloomParams",  bgfx::UniformType::Uniform4fv);
    g_postProcess.m_fade = createEngineUniform("u_fade", bgfx::UniformType::Uniform1f);
}

void Graphics::init(void* hwnd, bool bFullScreen)
{
    TIMELOG("Graphics::Init");
    bgfx::winSetHwnd((HWND)hwnd);
    bgfx::init(hwnd ? bgfx::RendererType::Direct3D11 : bgfx::RendererType::Null, &g_bgfxCallback);
    const bgfx::Caps* caps = bgfx::getCaps();
    bool shadowSamplerSupported = 0 != (caps->supported & BGFX_CAPS_TEXTURE_COMPARE_LEQUAL);
    LOGD("support shadow sampler = %d", shadowSamplerSupported);

    if(bFullScreen) g_resetFlag |= BGFX_RESET_FULLSCREEN;
    bgfx::reset(g_win32Context.m_width, g_win32Context.m_height, g_resetFlag);
    bgfx::setDebug(BGFX_DEBUG_TEXT);

    uint32_t clearViewId = (1 << kShadowViewId) | (1 << kBackgroundViewId);
    bgfx::setViewClearMask(clearViewId, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT, 0x303030ff, 1.0f, 0);

    PosTexCoord0Vertex::init();
    createUniforms();
    postProcessInit();

    g_camera.init();
    g_sceneMgr.init();
    g_debugDrawMgr.init();
    g_guiMgr.init();

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
        sprintf_s(buf, "h-blur-%d", i+1);
        bgfx::setViewName(kHDRBlurViewIdStart + i * 2 + 0, buf);
        sprintf_s(buf, "v-blur-%d", i+1);
        bgfx::setViewName(kHDRBlurViewIdStart + i * 2 + 1, buf);
    }
    bgfx::setViewName(kCombineViewId, "combine");
    bgfx::setViewName(kDebugDrawViewId, "debug");
    bgfx::setViewName(kGUIViewId, "gui");
}

void Graphics::postInit()
{
    extern  int  g_engineMode;
    if(g_engineMode == 1)
        return;

    TIMELOG("Graphics::PostInit");
    g_postProcess.m_blurShader = findShader("hdr_blur")->m_handle;
    g_postProcess.m_brightShader = findShader("hdr_bright")->m_handle;
    g_postProcess.m_combineShader = findShader("hdr_combine")->m_handle;
    g_status = 2;
    g_debugDrawMgr.ready();
}

void postProcessInit()
{
    int width = g_win32Context.m_width;
    int height = g_win32Context.m_height;
    
    int smSize = SHADOWMAP_SIZE;
    g_shadowMap.m_shadowMapSize = smSize;
    g_shadowMap.m_shadowMapFB = createFrameBuffer(smSize, smSize, 1, 1, false, bgfx::TextureFormat::D16, BGFX_TEXTURE_COMPARE_LEQUAL);

    uint32_t msaa = (g_resetFlag & BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
    uint32_t msaaMask = (msaa+1)<<BGFX_TEXTURE_RT_MSAA_SHIFT;
    bgfx::TextureFormat::Enum fboFmt = bgfx::TextureFormat::RGBA16F;
    FrameBufferTexture mainRtTextures[] = 
    {
        {fboFmt, msaaMask|BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP},    
        {bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_BUFFER_ONLY|msaaMask}
    };
    g_postProcess.m_colorFB = createFrameBuffer(width, height, 1, 1, true, BX_COUNTOF(mainRtTextures), mainRtTextures);
    int base = 2;
    for (int i = 0; i < N_PASSES; i++) {
        g_postProcess.m_blurFB[i][0] = createFrameBuffer(max(width / base, 1), max(height / base, 1), base, base, true, fboFmt);
        g_postProcess.m_blurFB[i][1] = createFrameBuffer(max(width / base, 1), max(height / base, 1), base, base, true, fboFmt);
        base *= 2;
    }

    g_postProcess.m_brightFB = createFrameBuffer(width/2, height/2, 1, 1, true, fboFmt);
    bx::mtxIdentity(g_postProcess.m_view);
    bx::mtxOrtho(g_postProcess.m_proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);

    g_postProcess.m_quadViewId = (1 << kHDRBrightViewId) | (1 << kCombineViewId);
    for (int i = 0; i < N_PASSES; ++i)
    {
        uint32_t hViewId = kHDRBlurViewIdStart + i*2 + 0;
        uint32_t vViewId = kHDRBlurViewIdStart + i*2 + 1;
        g_postProcess.m_quadViewId |= (1 << (hViewId));
        g_postProcess.m_quadViewId |= (1 << (vViewId));
    }

    g_status = 1;
}


void Graphics::quit()
{
    g_sceneMgr.quit();
    for (uint32_t i=0;i<g_numFrameBuffers;++i)
    {
        bgfx::destroyFrameBuffer(g_frameBuffers[i].m_handle);
    }
    for(uint32_t i=0; i<g_numEngineUniforms; ++i)
    {
        bgfx::destroyUniform(g_engineUniforms[i]);
    }
    g_guiMgr.destroy();
    bgfx::shutdown();
}

void Graphics::update(float dt)
{
    PROFILE(Graphics_Update);
    g_sceneMgr.update(dt);
    g_guiMgr.update(dt);
}

void submitPerFrameUniforms()
{
    extern float g_totalSeconds;
    bgfx::setUniform(g_uniformPerFrame.m_time, &g_totalSeconds);
    bgfx::setUniform(g_uniformPerFrame.m_camPos, g_camera.m_eye);
    float zparams[2] = {g_camera.m_near, g_camera.m_far};
    bgfx::setUniform(g_uniformPerFrame.m_zParams, zparams);
}

void submitShadowUniforms(ShadingEnviroment* env)
{
    if(!g_sceneMgr.m_shadowLight) return;

    extern float shadowLightView[16];
    extern float shadowLightProj[16];
    bgfx::setViewRect(kShadowViewId, 0, 0, g_shadowMap.m_shadowMapSize, g_shadowMap.m_shadowMapSize);
    bgfx::setViewFrameBuffer(kShadowViewId, g_shadowMap.m_shadowMapFB->m_handle);
    bgfx::setViewTransform(kShadowViewId, shadowLightView, shadowLightProj);
    bgfx::setUniform(g_shadowMap.m_paramUniform, env->m_shadowParams);

    const float mtxCrop[16] =
    {
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f,
    };

    float mtxTmp[16];
    float mtxShadow[16];
    bx::mtxMul(mtxTmp, shadowLightProj, mtxCrop);
    bx::mtxMul(mtxShadow, shadowLightView, mtxTmp);
    bgfx::setUniform(g_shadowMap.m_lightMtx, mtxShadow);
}

void Graphics::draw(ShadingEnviroment* env)
{
    //force clear color & depth executed.
    bgfx::submitMask((1<<kShadowViewId)|(1 << kBackgroundViewId));

    g_guiMgr.draw();

    //prepare for view rects.
    uint32_t screenViewId =  (1 << kBackgroundViewId) | (1 << kSceneViewId) | (1 << kDebugDrawViewId) | (1 << kCombineViewId);
    bgfx::setViewRectMask(screenViewId, 0, 0, g_win32Context.m_width, g_win32Context.m_height);

    uint32_t sceneViewId = (1 << kBackgroundViewId) | (1 << kSceneViewId) | (1 << kDebugDrawViewId);
    bgfx::setViewTransformMask(sceneViewId, g_camera.m_view, g_camera.m_proj);

    uint32_t colorViewId = (1 << kBackgroundViewId) | (1 << kSceneViewId) | (1<< kDebugDrawViewId);
    bgfx::setViewFrameBufferMask(colorViewId, g_postProcess.m_colorFB->m_handle);

    submitPerFrameUniforms();
    submitShadowUniforms(env);

    if(env) env->submit();
    g_sceneMgr.submit();
    g_debugDrawMgr.draw();
    postProcessSubmit(env);

    PROFILE(bgfx_frame);
    bgfx::frame();
}

void Graphics::frameStart()
{
    g_debugDrawMgr.frameStart();
    g_guiMgr.frameStart();
    bgfx::dbgTextClear(0, g_smallDebugDraw);
    g_dbgTexIndex = 0;
}

void Graphics::frameEnd()
{
    g_guiMgr.frameEnd();
}

void Graphics::resize( int w, int h )
{
    bgfx::reset(w, h, g_resetFlag);
    for (uint32_t i=0; i<g_numFrameBuffers; ++i)
    {
        FrameBuffer& fb = g_frameBuffers[i];
        if(!fb.m_scaled) continue;
        fb.resize(w, h);
    }
}

void postProcessSubmit(ShadingEnviroment* env)
{
    if(g_status < 1 || !env) return;
    int width = g_win32Context.m_width;
    int height = g_win32Context.m_height;

    bgfx::TextureHandle colorTex = g_postProcess.m_colorFB->m_textures[0];
    bgfx::TextureHandle depthTex = g_postProcess.m_colorFB->m_textures[1];
    float* dirParams = env->m_ppParams;
    bgfx::setViewTransformMask(g_postProcess.m_quadViewId, g_postProcess.m_view, g_postProcess.m_proj);

    FrameBuffer* fb = g_postProcess.m_brightFB;
    fb->begin(kHDRBrightViewId);
    Graphics::setTexture(TEX_COLOR_SLOT, colorTex);
    bgfx::setProgram(g_postProcess.m_brightShader);
    fb->end(kHDRBrightViewId);

    FrameBuffer* current = fb;
    for (uint32_t i = 0; i < N_PASSES; ++i)
    {
        FrameBuffer* hfb = g_postProcess.m_blurFB[i][0];
        FrameBuffer* vfb = g_postProcess.m_blurFB[i][1];

        uint32_t hViewId = kHDRBlurViewIdStart + i*2 + 0;
        uint32_t vViewId = kHDRBlurViewIdStart + i*2 + 1;

        // horizontalBlur
        hfb->begin(hViewId);
        Graphics::setTexture(TEX_COLOR_SLOT, current->m_handle);
        bgfx::setProgram(g_postProcess.m_blurShader);
        dirParams[0] = 1.0f;
        dirParams[1] = 0.0f;
        bgfx::setUniform(g_postProcess.m_ppUniform, dirParams);
        hfb->end(hViewId);

        //verticalBlur
        vfb->begin(vViewId);
        Graphics::setTexture(TEX_COLOR_SLOT, hfb->m_handle);
        bgfx::setProgram(g_postProcess.m_blurShader);
        dirParams[0] = 0.0f;
        dirParams[1] = 1.0f;
        bgfx::setUniform(g_postProcess.m_ppUniform, dirParams);
        vfb->end(vViewId);

        current = vfb;
    }

    bgfx::setViewRect(kCombineViewId, 0, 0, width, height);
    Graphics::setTexture(TEX_COLOR_SLOT, colorTex);
    for (int i = 1; i <= N_PASSES; ++i)
    {
        Graphics::setTexture(i, g_postProcess.m_blurFB[i-1][1]->m_handle);
    }
    Graphics::setTexture(N_PASSES+1, env->getCurrentColorGradingTex());
    bgfx::setProgram(g_postProcess.m_combineShader);
    bgfx::setState(postprocess_state);
    Graphics::screenSpaceQuad((float)width, (float)height);
    bgfx::submit(kCombineViewId);
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
        HK_ASSERT(0, bgfx::isValid(m_textures[i]));
    }

    m_handle = bgfx::createFrameBuffer(m_numTextures, m_textures, true);
    HK_ASSERT(0, bgfx::isValid(m_handle));
}

void FrameBuffer::begin(uint32_t viewId)
{
    bgfx::setViewRect(viewId, 0, 0, m_realSize[0], m_realSize[1]);
    bgfx::setViewFrameBuffer(viewId, m_handle);
}

void FrameBuffer::end(uint32_t viewId)
{
    bgfx::setState(postprocess_state);
    Graphics::screenSpaceQuad((float)m_realSize[0], (float)m_realSize[1]);
    bgfx::submit(viewId);
}

void Graphics::setTexture( int slot, bgfx::TextureHandle handle )
{
    bgfx::setTexture(slot, g_uniformPerObject.m_tex[slot], handle);
}

void Graphics::setTexture( int slot, bgfx::FrameBufferHandle handle )
{
    bgfx::setTexture(slot, g_uniformPerObject.m_tex[slot], handle);
}

void Graphics::screenSpaceQuad(float _textureWidth, float _textureHeight, float _width, float _height)
{
    if (!bgfx::checkAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_decl))
    {
        LOGE(__FUNCTION__" checkAvailTransientVertexBuffer failed.");
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

void Graphics::cull( float shadowArea, float shadowSize )
{
    PROFILE(Scene_Cull);
    g_sceneMgr.preCulling(g_camera.m_frustum, g_camera.m_eye, shadowArea, shadowSize);
}

//I don`t want gl&d3d9 support, but I don`t want to modify bgfx.cpp either
//so I add this -_-
namespace bgfx
{
    struct RendererContextI* rendererCreateGL() { return 0;};
    void rendererDestroyGL() {};
    struct RendererContextI* rendererCreateD3D9()  { return 0;};
    void rendererDestroyD3D9() {};
};


