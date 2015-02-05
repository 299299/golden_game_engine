#pragma once
#include "BaseCompiler.h"

class LookIKCompiler : public BaseCompiler
{
public:
    LookIKCompiler() {};
    ~LookIKCompiler() {};

    virtual std::string getFormatExt() const { return ""; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};

class ReachIKCompiler : public BaseCompiler
{
public:
    ReachIKCompiler(){};
    ~ReachIKCompiler(){};

    virtual std::string getFormatExt() const { return "";};
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};

class FootIKCompiler : public BaseCompiler
{
public:
    FootIKCompiler() {};
    ~FootIKCompiler() {};

    virtual std::string getFormatExt() const { return ""; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};