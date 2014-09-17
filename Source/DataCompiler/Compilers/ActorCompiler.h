#pragma once
#include "BaseCompiler.h"
#include "Actor.h"

class ActorCompiler : public BaseCompiler
{
public:
    ActorCompiler();
    ~ActorCompiler();

    virtual std::string getFormatExt() const { return ActorResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& jvalue);
};
