#include "Shader.h"
#include "Resource.h"
#include "Log.h"
#include "DataDef.h"
#include <bx/string.h>

void Shader::bringin()
{
    if(bgfx::isValid(m_handle)) return;
    m_handle = bgfx::createShader(bgfx::makeRef(m_blob, m_size));
    if(!bgfx::isValid(m_handle)) LOGE("Shader bringin error!");
}

void Shader::bringout()
{
    if(!bgfx::isValid(m_handle)) return;
    bgfx::destroyShader(m_handle);
    m_handle.idx = bgfx::invalidHandle;
}

void ShaderProgram::bringin()
{
    if(bgfx::isValid(m_handle)) return;
    if(!m_vs || !m_ps) return;
    m_handle = bgfx::createProgram(m_vs->m_handle, m_ps->m_handle, false);
    if(!bgfx::isValid(m_handle)) LOGE("ShaderProgram bringin error!");
}

void ShaderProgram::bringout()
{
    if(!bgfx::isValid(m_handle))
        return;
    bgfx::destroyProgram(m_handle);
    m_handle.idx = bgfx::invalidHandle;
}

void ShaderProgram::lookup()
{
    m_vs = FIND_RESOURCE(Shader, EngineTypes::SHADER, m_vsName);
    m_ps = FIND_RESOURCE(Shader, EngineTypes::SHADER, m_psName);
    if(!m_vs) LOGE("vs[%s] lookup error", stringid_lookup(m_vsName));
    if(!m_ps) LOGE("ps[%s] lookup error", stringid_lookup(m_psName));
}

void* load_resource_shader(void* data, uint32_t size)
{
    Shader* shader = (Shader*)data;
    shader->m_blob = (char*)data + sizeof(Shader);
    shader->m_handle.idx = bgfx::invalidHandle;
    return shader;
}

void bringin_resource_shader(void* resource)
{
    Shader* shader = (Shader*)resource;
    shader->bringin();
}

void bringout_resource_shader(void* resource)
{
    Shader* shader = (Shader*)resource;
    shader->bringout();
}

void lookup_resource_shader_program(void* resource)
{
    ShaderProgram* program = (ShaderProgram*)resource;
    program->lookup();
}

void bringin_resource_shader_program(void* resource)
{
    ShaderProgram* program = (ShaderProgram*)resource;
    program->bringin();
}

void bringout_resource_shader_program(void* resource)
{
    ShaderProgram* program = (ShaderProgram*)resource;
    program->bringout();
}

ShaderProgram* find_shader( const char* name )
{
    char buf[256];
    bx::snprintf(buf, sizeof(buf), PROGRAM_PATH"%s", name);
    return (ShaderProgram*)g_resourceMgr.find_resource(EngineTypes::PROGRAM, stringid_caculate(buf));
}
