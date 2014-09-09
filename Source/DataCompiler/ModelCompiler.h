#pragma once
#include "BaseCompiler.h"

class ModelCompiler : public BaseCompiler
{
public:
    ModelCompiler();
    ~ModelCompiler();

    virtual std::string getFormatExt() const { return ModelResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
