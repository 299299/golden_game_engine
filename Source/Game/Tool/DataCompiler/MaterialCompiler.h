#pragma once
#include "BaseCompiler.h"
#include "Material.h"

class MaterialCompiler : public BaseCompiler
{
public:
    MaterialCompiler();
    ~MaterialCompiler();

    virtual std::string getFormatExt() const { return Material::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
