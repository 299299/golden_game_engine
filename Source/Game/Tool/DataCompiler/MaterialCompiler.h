#pragma once
#include "BaseCompiler.h"

class MaterialCompiler : public BaseCompiler
{
public:
    MaterialCompiler();
    ~MaterialCompiler();

    virtual std::string getFormatExt() const { return EngineNames::MATERIAL; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
