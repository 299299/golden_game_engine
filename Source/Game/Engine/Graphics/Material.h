#pragma once
#include "StringId.h"
#include <bgfx.h>


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

ENGINE_NATIVE_ALIGN(struct) MatSampler
{
    Texture*                m_texture;
    uint32_t                m_flags;
    StringId                m_texture_name;

    uint8_t                 m_type;
    char                    m_padding[3];
};

ENGINE_NATIVE_ALIGN(struct) Material
{
    float                               m_offset_repeat[4];
    float                               m_diffuse[4];
    float                               m_specular[4];
    float                               m_params1[4];

    uint64_t                            m_state;

    ShaderProgram*                      m_shader;
    ShaderProgram*                      m_shadow_shader;
    StringId                            m_shader_name;
    StringId                            m_shadow_shader_name;

    uint32_t                            m_sampler_offset;
    uint32_t                            m_memory_size;

    uint8_t                             m_num_samplers;
    uint8_t                             m_flags;
    char                                m_padding[2];
};


void lookup_resource_material(void * resource);
void bringin_resource_material( void* resource );

void submit_material(Material* m);
void submit_material_shadow(Material* m);