#pragma once
#include "BaseCompiler.h"
#include "CommonUtils.h"
#include "Shader.h"

class ShaderCompiler : public BaseCompiler
{
public:
    ShaderCompiler();
    ~ShaderCompiler();

    virtual void preProcess();
    virtual std::string getFormatExt() const { return Shader::getName(); };
    virtual bool process(const std::string& input, const std::string& output);
};


class ProgramCompiler : public BaseCompiler
{
public:
    ProgramCompiler();
    ~ProgramCompiler();

    virtual std::string getFormatExt() const { return ShaderProgram::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};


class ShaderIncludeCompiler : public BaseCompiler
{
public:
    ShaderIncludeCompiler();
    ~ShaderIncludeCompiler();
    virtual bool checkProcessing();
    virtual std::string getFormatExt() const { return SHADER_INCLUDE_EXT; };
    virtual bool process(const std::string& input, const std::string& output);
};