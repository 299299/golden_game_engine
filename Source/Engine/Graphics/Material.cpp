#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "Resource.h"
#include "Graphics.h"
#include "Log.h"
#include <bx/bx.h>

void Material::lookup()
{
    m_shader = FIND_RESOURCE(ShaderProgram, m_shaderName);
    if(!m_shadowShaderName.isZero()) m_shadowShader = FIND_RESOURCE(ShaderProgram, m_shadowShaderName);

    for (uint32_t i=0; i<m_numSamplers; ++i) 
    {
        m_samplers[i].m_texture = FIND_RESOURCE(Texture, m_samplers[i].m_textureName);
    }
}

void Material::bringIn()
{
    for (uint32_t i=0; i<m_numSamplers; ++i)
    {
        MatSampler& sampler = m_samplers[i];
        Texture* tex = sampler.m_texture;
        if(!tex) continue;
        tex->bringIn(sampler.m_flags);
    }
}

void Material::changeTexture( int slot, const StringId& tex )
{
    MatSampler& sampler = m_samplers[slot];
    Texture* texture = FIND_RESOURCE(Texture, tex);
    if(!texture) return;
    sampler.m_texture = texture;
    texture->bringIn(sampler.m_flags);
}

void Material::submit() const
{
    if(!m_shader) return;
    bgfx::setProgram(m_shader->m_handle);
    uint32_t numSamplers = m_numSamplers;
    for (uint32_t i=0; i<numSamplers; ++i)
    {
        const MatSampler& sampler = m_samplers[i];
        if(!sampler.m_texture) continue;
        Graphics::setTexture(sampler.m_type, sampler.m_texture->m_handle);
    }
    // Set shadow map.
    extern ShadowMap            g_shadowMap;
    Graphics::setTexture(TEX_SHADOWMAP_SLOT, g_shadowMap.m_shadowMapFB->m_handle);

    extern UniformPerObject     g_uniformPerObject;
    bgfx::setUniform(g_uniformPerObject.m_uv, m_offsetAndRepeat);
    bgfx::setUniform(g_uniformPerObject.m_diffuse, m_diffuse);
    bgfx::setUniform(g_uniformPerObject.m_specular, m_specular);
    bgfx::setUniform(g_uniformPerObject.m_params1, m_params1);
    if(m_flags & kFlagRimLighting)
    {
        bgfx::setUniform(g_uniformPerObject.m_rimColorInfo, &m_rimColor);
    }
    if(m_flags & kFlagTranslucency)
    {
        bgfx::setUniform(g_uniformPerObject.m_skinRampOuterColor, m_translucency.m_rampOuterColor);
        bgfx::setUniform(g_uniformPerObject.m_skinRampMediumColor, m_translucency.m_rampMediumColor);
        bgfx::setUniform(g_uniformPerObject.m_skinRampInnerColor, m_translucency.m_rampInnerColor);
        bgfx::setUniform(g_uniformPerObject.m_translucencyInfo, m_translucency.m_info);
    }
    if(m_flags & kFlagOpacity)
    {
        bgfx::setUniform(g_uniformPerObject.m_opacityParams, m_opacityParams);
    }
    bgfx::setState(m_state);
}

void Material::submitShadow() const
{
    if(!m_shadowShader) return;

    bgfx::setProgram(m_shadowShader->m_handle);
    bgfx::setState(SHADOW_RENDER_STATE);
}

void Material::dump()
{
    LOGI("dump material ------------------>");
    LOGI("shader = %s, shadow-shader = %s", stringid_lookup(m_shaderName), stringid_lookup(m_shadowShaderName));
    LOGI("uv--> %f,%f,%f,%f", m_offsetAndRepeat[0], m_offsetAndRepeat[1], m_offsetAndRepeat[2], m_offsetAndRepeat[3]);
    LOGI("diffuse--> %f,%f,%f,%f", m_diffuse[0], m_diffuse[1], m_diffuse[2], m_diffuse[3]);
    LOGI("specular--> %f,%f,%f,%f", m_specular[0], m_specular[1], m_specular[2], m_specular[3]);
    LOGI("params1--> %f,%f,%f,%f", m_params1[0], m_params1[1], m_params1[2], m_params1[3]);
    LOGI("opacity--> %f,%f,%f,%f", m_opacityParams[0], m_opacityParams[1], m_opacityParams[2], m_opacityParams[3]);
    LOGI("state = %llu, num-samplers = %u, flags = %d", m_state, m_numSamplers, m_flags);
}

void* load_resource_material(const char* data, uint32_t size)
{
    Material* m = (Material*)data;
    m->m_samplers = (MatSampler*)(data + sizeof(Material));
#ifdef DUMP_RESOURCE
    m->dump();
#endif
    return m;
}

void lookup_resource_material(void * resource)
{
    Material* mat = (Material*)resource;
    mat->lookup();
}

void bringin_resource_material( void* resource )
{
    Material* mat = (Material*)resource;
    mat->bringIn();
}
