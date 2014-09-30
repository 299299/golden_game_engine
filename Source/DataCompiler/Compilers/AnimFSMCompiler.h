#pragma once
#include "BaseCompiler.h"
#include "AnimFSM.h"

class AnimFSMCompiler : public BaseCompiler
{
public:
    AnimFSMCompiler();
    ~AnimFSMCompiler();

    virtual std::string getFormatExt() const { return AnimFSM::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
    virtual bool checkInLevel() const { return false; };
};
