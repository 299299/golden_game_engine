#pragma once
#include "BaseCompiler.h"

class ModelCompiler : public BaseCompiler
{
public:
    ModelCompiler();
    ~ModelCompiler();

    virtual std::string getFormatExt() const { return EngineNames::MODEL; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
