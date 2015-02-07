#pragma once
#include "StringId.h"
#include <bgfx.h>


#define SHADOW_RENDER_STATE  (BGFX_STATE_ALPHA_WRITE|BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_CULL_CCW)

enum TextureFlag
{
    kTex_U_Mirror           = (1 << 0),
    kTex_U_Clamp            = (1 << 1),
    kTex_V_Mirror           = (1 << 2),
    kTex_V_Clamp            = (1 << 3),
    kTex_W_Mirror           = (1 << 4),
    kTex_W_Clamp            = (1 << 5),
    kTex_Min_Point          = (1 << 6),
    kTex_Min_Anisotropic    = (1 << 7),
    kTex_Mag_Point          = (1 << 8),
    kTex_Mag_Anisotropic    = (1 << 8),
    kTex_Mip_Point          = (1 << 10),
};

enum MaterialFlag
{
    kFlagSkinning           = (1 << 0),
    kFlagAlphaMask          = (1 << 1),
    kFlagRimLighting        = (1 << 2),
    kFlagTranslucency       = (1 << 3),
    kFlagOpacity            = (1 << 4),
};

struct Texture;
struct ShaderProgram;
struct RimColorInfo
{
    float           m_rimFresnelMin;
    float           m_rimFresnelMax;
    float           m_rimBrightness;
};

struct TranslucencyInfo
{
    float           m_rampOuterColor[3];
    float           m_rampMediumColor[3];
    float           m_rampInnerColor[3];
    float           m_info[4];
};

ENGINE_NATIVE_ALIGN(struct) MatSampler
{
    Texture*                m_texture;
    uint32_t                m_flags;
    StringId                m_textureName;

    uint8_t                 m_type;
    char                    m_padding[3];
};

ENGINE_NATIVE_ALIGN(struct) Material
{
    void lookup();
    void bringin();
    void change_texture(int slot, StringId tex);
    void submit() const;
    void submit_shadow() const;

    float                               m_offsetAndRepeat[4];
    float                               m_diffuse[4];
    float                               m_specular[4];
    float                               m_params1[4];
    float                               m_opacityParams[3];

    uint64_t                            m_state;
    MatSampler*                         m_samplers;

    RimColorInfo                        m_rimColor;
    TranslucencyInfo                    m_translucency;

    ShaderProgram*                      m_shader;
    ShaderProgram*                      m_shadowShader;
    StringId                            m_shaderName;
    StringId                            m_shadowShaderName;

    uint8_t                             m_numSamplers;
    uint8_t                             m_flags;
    char                                m_padding[2];
};


void* load_resource_material(void* data, uint32_t size);
void lookup_resource_material(void * resource);
void bringin_resource_material( void* resource );