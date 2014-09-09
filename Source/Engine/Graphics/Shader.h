#pragma once
#include "StringId.h"
#include <bgfx.h>

struct ResourcePackage;
struct Shader;
struct ShaderProgram;

#define PROGRAM_PATH         "core/programs/"
#define SHADER_PATH          "core/shaders/"

ENGINE_NATIVE_ALIGN struct Shader
{
    DECLARE_RESOURCE(shader);

    StringId                    m_name;
    char*                       m_blob;
    uint32_t                    m_size;
    bgfx::ShaderHandle          m_handle;
    char                        m_padding[2];
        
    void bringIn();
    void bringOut();
};

ENGINE_NATIVE_ALIGN struct ShaderProgram
{
    DECLARE_RESOURCE(program);

    void lookup();
    void bringIn();
    void bringOut();

    bgfx::ProgramHandle         m_handle;
    Shader*                     m_ps;
    Shader*                     m_vs;
    StringId                    m_psName;
    StringId                    m_vsName;
};

void* load_resource_shader(const char* data, uint32_t size);
void bringin_resource_shader(void* resource);
void bringout_resource_shader(void* resource);

void lookup_resource_shader_program(void* resource);
void bringin_resource_shader_program(void* resource);
void bringout_resource_shader_program(void* resource);

ShaderProgram* findShader(const char* name);
