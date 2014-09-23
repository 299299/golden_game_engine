#pragma once
#include "BaseCompiler.h"
#include "Animation.h"

class AnimationCompiler : public BaseCompiler
{
public:
    AnimationCompiler();
    ~AnimationCompiler();

    virtual std::string getFormatExt() const { return Animation::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
