#pragma once
#include "BaseCompiler.h"

class AnimationStateCompiler : public BaseCompiler
{
public:
    AnimationStateCompiler();
    ~AnimationStateCompiler();

    virtual std::string getFormatExt() const { return EngineNames::ANIMATION_STATES; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
