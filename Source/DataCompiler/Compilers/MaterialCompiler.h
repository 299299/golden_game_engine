#pragma once
#include "BaseCompiler.h"
#include "Material.h"

class MaterialCompiler : public BaseCompiler
{
public:
    MaterialCompiler();
    ~MaterialCompiler();

    virtual std::string getFormatExt() const { return Material::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
