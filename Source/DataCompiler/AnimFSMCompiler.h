#pragma once
#include "BaseCompiler.h"

class AnimFSMCompiler : public BaseCompiler
{
public:
    AnimFSMCompiler();
    ~AnimFSMCompiler();

    virtual std::string getFormatExt() const { return AnimFSM::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
