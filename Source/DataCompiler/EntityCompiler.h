#pragma once
#include "BaseCompiler.h"
#include "Entity.h"

class EntityCompiler : public BaseCompiler
{
public:
    EntityCompiler();
    ~EntityCompiler();

    virtual std::string getFormatExt() const { return EntityResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& jvalue);
};
