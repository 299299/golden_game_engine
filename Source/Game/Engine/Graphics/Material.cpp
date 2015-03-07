#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "Resource.h"
#include "Graphics.h"
#include "Log.h"
#include "DataDef.h"
#include <bx/bx.h>

#define SHADOW_RENDER_STATE  (BGFX_STATE_ALPHA_WRITE|BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_CULL_CCW)

void lookup_resource_material(void * resource)
{
    Material* mat = (Material*)resource;
    mat->m_shader = FIND_RESOURCE(ShaderProgram, EngineTypes::PROGRAM, mat->m_shader_name);
    StringId _shadow_shader_name = mat->m_shadow_shader_name;
    if(_shadow_shader_name != 0)
        mat->m_shadow_shader = FIND_RESOURCE(ShaderProgram, EngineTypes::PROGRAM, _shadow_shader_name);

    uint32_t _num = mat->m_num_samplers;
    MatSampler* _samplers = (MatSampler*)((char*)resource + mat->m_sampler_offset);

    for (uint32_t i=0; i<_num; ++i)
    {
        MatSampler* _sample = _samplers + i;
        _sample->m_texture = FIND_RESOURCE(Texture, EngineTypes::TEXTURE, _sample->m_texture_name);
    }
}

void bringin_resource_material( void* resource )
{
    Material* mat = (Material*)resource;
    uint32_t _num = mat->m_num_samplers;
    MatSampler* _samplers = (MatSampler*)((char*)resource + mat->m_sampler_offset);

    for (uint32_t i=0; i<_num; ++i)
    {
        MatSampler* _sample = _samplers + i;
        Texture* _tex = _sample->m_texture;
        if(!_tex)
            continue;
        bringin_resource_texture(_tex, _sample->m_flags);
    }
}


void submit_material(Material* m)
{
    if(!m->m_shader || !bgfx::isValid(m->m_shader->m_handle))
        return;

    bgfx::setProgram(m->m_shader->m_handle);
    uint32_t _num = m->m_num_samplers;
    MatSampler* _samplers = (MatSampler*)((char*)m + m->m_sampler_offset);

    for (uint32_t i=0; i<_num; ++i)
    {
        MatSampler* _sample = _samplers + i;
        Texture* _tex = _sample->m_texture;
        if(!_tex)
            continue;
        Graphics::set_texture(_sample->m_type, _tex->m_handle);
    }

    // Set shadow map.
    extern ShadowMap g_shadowMap;
    if(g_shadowMap.m_shadowMapFB)
        Graphics::set_texture(TEX_SHADOWMAP_SLOT, g_shadowMap.m_shadowMapFB->m_handle);

    extern UniformPerObject     g_uniformPerObject;
    bgfx::setUniform(g_uniformPerObject.m_uv, m->m_offset_scale);
    bgfx::setUniform(g_uniformPerObject.m_diffuse, m->m_diffuse);
    bgfx::setUniform(g_uniformPerObject.m_specular, m->m_specular);
    bgfx::setUniform(g_uniformPerObject.m_params1, m->m_params1);
    bgfx::setState(m->m_state);
}

void submit_material_shadow(Material* m)
{
    ShaderProgram* _shadow = m->m_shadow_shader;
    if(!_shadow)
        return;
    bgfx::setProgram(_shadow->m_handle);
    bgfx::setState(SHADOW_RENDER_STATE);
}