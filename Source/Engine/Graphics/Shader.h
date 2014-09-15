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

ShaderProgram* findShader(const char* name);
