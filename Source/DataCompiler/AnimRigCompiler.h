#pragma once
#include "BaseCompiler.h"

class AnimRigCompiler : public BaseCompiler
{
public:
    AnimRigCompiler();
    ~AnimRigCompiler();

    virtual std::string getFormatExt() const { return AnimRig::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};