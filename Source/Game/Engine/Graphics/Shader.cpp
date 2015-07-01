#include "Shader.h"
#include "Resource.h"
#include "Log.h"
#include "DataDef.h"
#include <bx/string.h>

#define DESTROY_SHADER(handle) \
        if(bgfx::isValid(handle)) {\
            bgfx::destroyShader(handle);\
            handle.idx = bgfx::invalidHandle;\
        }

int bringin_resource_shader(void* resource)
{
    Shader* shader = (Shader*)resource;
    if(bgfx::isValid(shader->m_handle))
        return 0;
    shader->m_handle = bgfx::createShader(
        bgfx::makeRef((char*)resource + shader->m_data_offset, shader->m_data_size));
    return bgfx::isValid(shader->m_handle) ? 0 : -1;
}

void bringout_resource_shader(void* resource)
{
    Shader* shader = (Shader*)resource;
    DESTROY_SHADER(shader->m_handle);
}

void lookup_resource_shader_program(void* resource)
{
    ShaderProgram* program = (ShaderProgram*)resource;
    program->m_vs = FIND_RESOURCE(Shader, EngineTypes::SHADER, program->m_vsName);
    program->m_ps = FIND_RESOURCE(Shader, EngineTypes::SHADER, program->m_psName);
    if(!program->m_vs)
        LOGE("vs[%s] lookup error", stringid_lookup(program->m_vsName));
    if(!program->m_ps)
        LOGE("ps[%s] lookup error", stringid_lookup(program->m_psName));
}

int bringin_resource_shader_program(void* resource)
{
    ShaderProgram* program = (ShaderProgram*)resource;
    if(bgfx::isValid(program->m_handle))
        return 0;
    Shader* vs = program->m_vs;
    Shader* ps = program->m_ps;
    if(!vs || !ps)
        return -1;
    if(!bgfx::isValid(vs->m_handle) || !bgfx::isValid(ps->m_handle))
        return -1;
    program->m_handle = bgfx::createProgram(
        program->m_vs->m_handle,
        program->m_ps->m_handle, false);
    if(!bgfx::isValid(program->m_handle)) {
        LOGE("ShaderProgram bringin vs=%s, ps=%s error!", stringid_lookup(program->m_vsName), stringid_lookup(program->m_psName));
        return -1;
    }
    return 0;
}

void bringout_resource_shader_program(void* resource)
{
    ShaderProgram* program = (ShaderProgram*)resource;
    if(!bgfx::isValid(program->m_handle))
        return;
    bgfx::destroyProgram(program->m_handle);
    program->m_handle.idx = bgfx::invalidHandle;
}
