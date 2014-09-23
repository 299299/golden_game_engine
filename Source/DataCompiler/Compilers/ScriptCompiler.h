#pragma once
#include "BaseCompiler.h"
#include "Script.h"

class ScriptCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return ScriptResource::get_name(); };
    virtual bool process(const std::string& input, const std::string& output);
};