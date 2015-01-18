#pragma once
#include "BaseCompiler.h"
#include "Ragdoll.h"

class RagdollCompiler : public BaseCompiler
{
public:
    RagdollCompiler();
    ~RagdollCompiler();

    virtual std::string getFormatExt() const { return RagdollResource::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};