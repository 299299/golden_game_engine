#pragma once
#include "BaseCompiler.h"
#include "Script.h"

class ScriptCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return ScriptResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};