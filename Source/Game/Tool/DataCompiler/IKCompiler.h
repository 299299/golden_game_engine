#pragma once
#include "BaseCompiler.h"
#include "IK.h"

class LookIKCompiler : public BaseCompiler
{
public:
    LookIKCompiler() {};
    ~LookIKCompiler() {};

    virtual std::string getFormatExt() const { return LookAtResource::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};

class ReachIKCompiler : public BaseCompiler
{
public:
    ReachIKCompiler(){};
    ~ReachIKCompiler(){};

    virtual std::string getFormatExt() const { return ReachResource::get_name();};
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};

class FootIKCompiler : public BaseCompiler
{
public:
    FootIKCompiler() {};
    ~FootIKCompiler() {};

    virtual std::string getFormatExt() const { return FootResource::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};