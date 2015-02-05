#pragma once
#include "BaseCompiler.h"

class ShaderCompiler : public BaseCompiler
{
public:
    ShaderCompiler();
    ~ShaderCompiler();

    virtual void preProcess();
    virtual std::string getFormatExt() const { return EngineNames::SHADER; };
    virtual bool process(const std::string& input, const std::string& output);
};


class ProgramCompiler : public BaseCompiler
{
public:
    ProgramCompiler();
    ~ProgramCompiler();

    virtual std::string getFormatExt() const { return EngineNames::PROGRAM; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
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