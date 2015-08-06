#pragma once
#include "StringId.h"
#include <bgfx.h>

#define MAX_COLOR_GRADING_NUM               (6)

struct Texture;
struct Texture3D;
struct ShaderProgram;

ENGINE_NATIVE_ALIGN(struct) ShadingEnviroment
{
    void update(float dt);
    void submit();
    void lookup();

    bgfx::TextureHandle get_colorgrading_tex() const;

    float                               m_ambient_sky_color[3];
    float                               m_ambient_ground_color[3];
    float                               m_fog_params[4];

    float                               m_shadow_area_size;
    float                               m_shadow_far;
    float                               m_shadow_params[3];

    uint32_t                            m_num_colorgrading_textures;
    int                                 m_colorgrading_index;
    Texture3D*                          m_color_grading_textures[MAX_COLOR_GRADING_NUM];
    StringId                            m_color_grading_texturenames[MAX_COLOR_GRADING_NUM];
};

void  lookup_resource_shading_enviroment(void* resource);