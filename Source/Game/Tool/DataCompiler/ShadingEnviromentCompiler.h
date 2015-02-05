#pragma once
#include "BaseCompiler.h"

class ShadingEnviromentCompiler : public BaseCompiler
{
public:
    ShadingEnviromentCompiler();
    ~ShadingEnviromentCompiler();

    virtual std::string getFormatExt() const { return EngineNames::SHADING_ENV; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
