#pragma once
#include "StringId.h"
#include "ShaderInc.h"
#include <bgfx.h>

struct UniformPerFrame
{
    bgfx::UniformHandle                 m_time;
    bgfx::UniformHandle                 m_camPos;
    bgfx::UniformHandle                 m_zParams;
    bgfx::UniformHandle                 m_ambientSkyColor;
    bgfx::UniformHandle                 m_ambientGroundColor;
    bgfx::UniformHandle                 m_fogParams;
};

struct UniformPerObject
{
    bgfx::UniformHandle                 m_tex[TEX_MAX_SLOT];
    bgfx::UniformHandle                 m_uv;
    bgfx::UniformHandle                 m_diffuse;
    bgfx::UniformHandle                 m_specular;
    bgfx::UniformHandle                 m_rimColorInfo;
    bgfx::UniformHandle                 m_translucencyInfo;
    bgfx::UniformHandle                 m_opacityParams;
    bgfx::UniformHandle                 m_skinRampOuterColor;
    bgfx::UniformHandle                 m_skinRampMediumColor;
    bgfx::UniformHandle                 m_skinRampInnerColor;
    bgfx::UniformHandle                 m_params1;
};

struct UniformPerLight
{
    bgfx::UniformHandle                 m_color;
    bgfx::UniformHandle                 m_vec;
    bgfx::UniformHandle                 m_info;
    bgfx::UniformHandle                 m_type;
};
    

struct FrameBufferTexture
{
    bgfx::TextureFormat::Enum           m_format;
    uint32_t                            m_flag;
};

struct FrameBuffer
{
    int                                 m_realSize[2];
    int                                 m_sizeDiv[2];
    FrameBufferTexture                  m_texInfo[4];
    bgfx::TextureHandle                 m_textures[4];
    bgfx::FrameBufferHandle             m_handle;
    uint8_t                             m_numTextures;
    bool                                m_scaled;

    void create();
    void resize(int w, int h);
    void begin(uint32_t viewId);
    void end(uint32_t viewId);
        
};

struct ShadowMap
{
    FrameBuffer*                        m_shadowMapFB;
    bgfx::UniformHandle                 m_lightMtx;
    bgfx::UniformHandle                 m_paramUniform;
    int                                 m_shadowMapSize;
};


struct PostProcess
{
    float                               m_view[16];
    float                               m_proj[16];

    bgfx::ProgramHandle                 m_brightShader;
    bgfx::ProgramHandle                 m_blurShader;
    bgfx::ProgramHandle                 m_combineShader;

    bgfx::UniformHandle                 m_ppUniform;
    bgfx::UniformHandle                 m_bloomUniform;
    bgfx::UniformHandle                 m_fade;

    FrameBuffer*                        m_colorFB;
    FrameBuffer*                        m_brightFB;
    FrameBuffer*                        m_blurFB[N_PASSES][2]; // hblur + vblur
};

struct ShadingEnviroment;
struct Graphics
{
    static void init(void* hwnd, bool bFullScreen = false);
    static void ready();
    static void shutdown();
    static void draw(ShadingEnviroment* env);
    static void update(ShadingEnviroment* env, float dt);
    static void frame_start();
    static void frame_end();
    static void screenspace_quad(float _textureWidth, float _textureHeight, float _width = 1.0f, float _height = 1.0f);
    static void set_texture(int slot, bgfx::TextureHandle handle);
    static void set_texture(int slot, bgfx::FrameBufferHandle handle);
    static void register_factories();
};