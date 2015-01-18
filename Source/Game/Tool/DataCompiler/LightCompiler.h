#pragma once
#include "BaseCompiler.h"
#include "Light.h"

class LightCompiler : public BaseCompiler
{
public:
    LightCompiler();
    ~LightCompiler();

    virtual std::string getFormatExt() const { return LightResource::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
