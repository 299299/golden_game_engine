#pragma once
#include "BaseCompiler.h"

class ProxyCompiler : public BaseCompiler
{
public:
    ProxyCompiler();
    ~ProxyCompiler();

    virtual std::string getFormatExt() const { return ProxyResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
