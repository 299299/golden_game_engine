#pragma once
#include "BaseCompiler.h"
#include "IK.h"

class LookIKCompiler : public BaseCompiler
{
public:
    LookIKCompiler() {};
    ~LookIKCompiler() {};

    virtual std::string getFormatExt() const { return LookAtResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};

class ReachIKCompiler : public BaseCompiler
{
public:
    ReachIKCompiler(){};
    ~ReachIKCompiler(){};

    virtual std::string getFormatExt() const { return ReachResource::getName();};
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};

class FootIKCompiler : public BaseCompiler
{
public:
    FootIKCompiler() {};
    ~FootIKCompiler() {};

    virtual std::string getFormatExt() const { return FootResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};