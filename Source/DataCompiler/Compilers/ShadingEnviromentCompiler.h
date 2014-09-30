#pragma once
#include "BaseCompiler.h"
#include "ShadingEnviroment.h"

class ShadingEnviromentCompiler : public BaseCompiler
{
public:
    ShadingEnviromentCompiler();
    ~ShadingEnviromentCompiler();

    virtual std::string getFormatExt() const { return ShadingEnviroment::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
    virtual bool checkProcessing() { return true; };
};
