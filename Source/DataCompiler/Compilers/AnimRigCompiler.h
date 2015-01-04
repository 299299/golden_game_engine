#pragma once
#include "BaseCompiler.h"
#include "AnimRig.h"

class AnimRigCompiler : public BaseCompiler
{
public:
    AnimRigCompiler();
    ~AnimRigCompiler();

    virtual std::string getFormatExt() const { return AnimRig::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
    virtual bool checkInLevel() const { return false; };
};