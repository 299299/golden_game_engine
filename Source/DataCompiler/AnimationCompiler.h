#pragma once
#include "BaseCompiler.h"

class AnimationCompiler : public BaseCompiler
{
public:
    AnimationCompiler();
    ~AnimationCompiler();

    virtual std::string getFormatExt() const { return Animation::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
