#pragma once
#include "BaseCompiler.h"

class AnimRigCompiler : public BaseCompiler
{
public:
    AnimRigCompiler();
    ~AnimRigCompiler();

    virtual std::string getFormatExt() const { return EngineNames::ANIMATION_RIG; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};