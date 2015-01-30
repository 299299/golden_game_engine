#pragma once
#include "BaseCompiler.h"
#include "AnimationState.h"

class AnimationStateCompiler : public BaseCompiler
{
public:
    AnimationStateCompiler();
    ~AnimationStateCompiler();

    virtual std::string getFormatExt() const { return AnimationStateLayer::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};
