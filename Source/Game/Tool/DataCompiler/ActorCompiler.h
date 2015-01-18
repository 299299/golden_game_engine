#pragma once
#include "BaseCompiler.h"
#include "Actor.h"

class ActorCompiler : public BaseCompiler
{
public:
    ActorCompiler();
    ~ActorCompiler();

    virtual std::string getFormatExt() const { return ActorResource::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
