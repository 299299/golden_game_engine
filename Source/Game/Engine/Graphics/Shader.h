#pragma once
#include "StringId.h"
#include <bgfx.h>

struct ResourcePackage;
struct Shader;
struct ShaderProgram;

#define PROGRAM_PATH         "core/programs/"
#define SHADER_PATH          "core/shaders/"

struct Shader
{
    uint32_t                    m_data_offset;
    uint32_t                    m_data_size;
    bgfx::ShaderHandle          m_handle;
};

struct ShaderProgram
{
    bgfx::ProgramHandle         m_handle;
    Shader*                     m_ps;
    Shader*                     m_vs;
    StringId                    m_psName;
    StringId                    m_vsName;
};

int  bringin_resource_shader(void* resource);
void bringout_resource_shader(void* resource);

void lookup_resource_shader_program(void* resource);
int  bringin_resource_shader_program(void* resource);
void bringout_resource_shader_program(void* resource);
