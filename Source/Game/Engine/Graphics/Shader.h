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
    StringId                    m_name;
    char*                       m_blob;
    uint32_t                    m_size;
    bgfx::ShaderHandle          m_handle;
    char                        m_padding[2];

    void bringin();
    void bringout();
};

ENGINE_NATIVE_ALIGN(struct) ShaderProgram
{
    void lookup();
    void bringin();
    void bringout();

    bgfx::ProgramHandle         m_handle;
    Shader*                     m_ps;
    Shader*                     m_vs;
    StringId                    m_psName;
    StringId                    m_vsName;
};

ShaderProgram* find_shader(const char* name);
