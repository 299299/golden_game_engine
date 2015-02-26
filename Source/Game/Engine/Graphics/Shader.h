#pragma once
#include "StringId.h"
#include <bgfx.h>

struct ResourcePackage;
struct Shader;
struct ShaderProgram;

#define PROGRAM_PATH         "core/programs/"
#define SHADER_PATH          "core/shaders/"

ENGINE_NATIVE_ALIGN(struct) Shader
{
    uint32_t                    m_data_offset;
    uint32_t                    m_data_size;
    bgfx::ShaderHandle          m_handle;
};

ENGINE_NATIVE_ALIGN(struct) ShaderProgram
{
    bgfx::ProgramHandle         m_handle;
    Shader*                     m_ps;
    Shader*                     m_vs;
    StringId                    m_psName;
    StringId                    m_vsName;
};

void bringin_resource_shader(void* resource);
void bringout_resource_shader(void* resource);

void lookup_resource_shader_program(void* resource);
void bringin_resource_shader_program(void* resource);
void bringout_resource_shader_program(void* resource);
