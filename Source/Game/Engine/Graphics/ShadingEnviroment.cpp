#include "ShadingEnviroment.h"
#include "Resource.h"
#include "Texture.h"
#include "Graphics.h"
#include "Shader.h"
#include "Win32Context.h"
#include "DataDef.h"
#include "Prerequisites.h"
#include <bx/fpumath.h>
#include <stdio.h>

void ShadingEnviroment::update( float dt )
{

}

void ShadingEnviroment::submit()
{
    extern UniformPerFrame      g_uniformPerFrame;
    bgfx::setUniform(g_uniformPerFrame.m_ambientSkyColor, m_ambient_sky_color);
    bgfx::setUniform(g_uniformPerFrame.m_ambientGroundColor, m_ambient_ground_color);
    bgfx::setUniform(g_uniformPerFrame.m_fogParams, m_fog_params);
}

bgfx::TextureHandle ShadingEnviroment::get_colorgrading_tex() const
{
    return m_color_grading_textures[m_colorgrading_index]->m_handle;
}

void lookup_resource_shading_enviroment( void* resource )
{
    ShadingEnviroment* env = (ShadingEnviroment*)resource;
    uint32_t num = env->m_num_colorgrading_textures;
    Texture3D** head = env->m_color_grading_textures;
    StringId* names = env->m_color_grading_texturenames;
    for (uint32_t i=0; i<num; ++i)
    {
        head[i] = FIND_RESOURCE(Texture3D, EngineTypes::TEXTURE_3D, names[i]);
        ENGINE_ASSERT(head[i], "can not find color-grading texture.");
    }
}