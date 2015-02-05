#pragma once
#include "BaseCompiler.h"

class TextureCompiler : public BaseCompiler
{
public:
    TextureCompiler();
    virtual std::string getFormatExt() const { return EngineNames::TEXTURE; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
    virtual void postProcess();
    bool processImage(const std::string& input, const std::string& output);
    std::string         m_format;
};

class DDSCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return EngineNames::TEXTURE; };
    virtual bool process(const std::string& input, const std::string& output);
};

class Texture3DCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return EngineNames::TEXTURE_3D; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};

class Texture2DCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return EngineNames::TEXTURE_2D; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};