#pragma once
#include "BaseCompiler.h"

class PhysicsCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return EngineNames::PHYSICS; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};

class ProxyCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return ""; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
};


class PhysicsConfigCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return EngineNames::PHYSICS_CONFIG; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);

    int findFilterIndex(const std::string& name) const;
private:
    StringArray             m_filterNames;
};