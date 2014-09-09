#pragma once
#include "BaseCompiler.h"

class TextureCompiler : public BaseCompiler
{
public:
    TextureCompiler();
    virtual std::string getFormatExt() const { return Texture::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
    virtual void postProcess();
    bool processImage(const std::string& input, const std::string& output);
    std::string         m_format;
};

class DDSCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return Texture::getName(); };
    virtual bool process(const std::string& input, const std::string& output);
};

class Texture3DCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return Raw3DTexture::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};

class Texture2DCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return Raw2DTexture::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};