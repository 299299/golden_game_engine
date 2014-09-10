#pragma once
#include "BaseCompiler.h"
#include "Ragdoll.h"

class RagdollCompiler : public BaseCompiler
{
public:
    RagdollCompiler();
    ~RagdollCompiler();

    virtual std::string getFormatExt() const { return RagdollResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};