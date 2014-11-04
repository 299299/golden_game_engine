#pragma once
#include "BaseCompiler.h"
#include "Movement.h"

class MovementCompiler : public BaseCompiler
{
public:
    MovementCompiler();
    ~MovementCompiler();

    virtual std::string getFormatExt() const { return MovementResource::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};
