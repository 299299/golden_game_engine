#pragma once
#include "BaseCompiler.h"

class PhysicsCompiler : public BaseCompiler
{
public:
    PhysicsCompiler();
    ~PhysicsCompiler();

    virtual std::string getFormatExt() const { return PhysicsResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
