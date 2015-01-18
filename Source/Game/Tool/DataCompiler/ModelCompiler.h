#pragma once
#include "BaseCompiler.h"
#include "Model.h"

class ModelCompiler : public BaseCompiler
{
public:
    ModelCompiler();
    ~ModelCompiler();

    virtual std::string getFormatExt() const { return ModelResource::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
