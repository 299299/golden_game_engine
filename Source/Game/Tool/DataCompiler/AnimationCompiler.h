#pragma once
#include "BaseCompiler.h"

class AnimationCompiler : public BaseCompiler
{
public:
    AnimationCompiler();
    ~AnimationCompiler();

    virtual std::string getFormatExt() const { return EngineNames::ANIMATION; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
