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
    extern PostProcess          g_postProcess;

    bgfx::setUniform(g_uniformPerFrame.m_ambientSkyColor, m_ambientSkyColor);
    bgfx::setUniform(g_uniformPerFrame.m_ambientGroundColor, m_ambientGroundColor);
    bgfx::setUniform(g_uniformPerFrame.m_fogParams, m_fogParams);

    bgfx::setUniform(g_postProcess.m_ppUniform, m_ppParams);
    bgfx::setUniform(g_postProcess.m_bloomUniform, m_bloomParams);

}

void ShadingEnviroment::lookup()
{
    uint32_t num = m_numColorgradingTextures;
    Raw3DTexture** head = m_colorGradingTextures;
    StringId* names = m_colorgradingTextureNames;
    for (uint32_t i=0; i<num; ++i)
    {
        head[i] = FIND_RESOURCE(Raw3DTexture, EngineTypes::TEXTURE_3D, names[i]);
        ENGINE_ASSERT(head[i], "can not find color-grading texture.");
    }
}

bgfx::TextureHandle ShadingEnviroment::get_colorgrading_tex() const
{
    return m_colorGradingTextures[m_colorGradingIndex]->m_handle;
}

void lookup_resource_shading_enviroment( void* resource )
{
    ((ShadingEnviroment*)resource)->lookup();
}