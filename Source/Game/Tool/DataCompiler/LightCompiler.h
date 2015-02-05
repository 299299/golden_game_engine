#pragma once
#include "BaseCompiler.h"

class LightCompiler : public BaseCompiler
{
public:
    LightCompiler();
    ~LightCompiler();

    virtual std::string getFormatExt() const { return EngineNames::LIGHT; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
