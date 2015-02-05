#pragma once
#include "BaseCompiler.h"

class ActorCompiler : public BaseCompiler
{
public:
    ActorCompiler();
    ~ActorCompiler();

    virtual std::string getFormatExt() const { return EngineNames::ACTOR };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
