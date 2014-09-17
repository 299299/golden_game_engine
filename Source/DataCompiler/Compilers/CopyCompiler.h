#pragma once
#include "BaseCompiler.h"

class CopyCompiler : public BaseCompiler
{
public:
    CopyCompiler();
    ~CopyCompiler();

    virtual std::string getFormatExt() const { return "copy"; };
    virtual bool process(const std::string& input, const std::string& output);
};
