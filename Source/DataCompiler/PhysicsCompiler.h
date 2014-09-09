#pragma once
#include "BaseCompiler.h"

class PhysicsCompiler : public BaseCompiler
{
public:
    PhysicsCompiler();
    ~PhysicsCompiler();

    virtual std::string getFormatExt() const { return PhysicsResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};


class PhysicsConfigCompiler : public BaseCompiler
{
public:
    PhysicsConfigCompiler();
    ~PhysicsConfigCompiler();

    virtual std::string getFormatExt() const { return PhysicsConfig::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);

    int findFilterIndex(const std::string& name) const;
private:
    std::vector<std::string>    m_filterNames;
};