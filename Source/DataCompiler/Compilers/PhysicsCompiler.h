#pragma once
#include "BaseCompiler.h"
#include "PhysicsWorld.h"
#include "PhysicsInstance.h"
#include "ProxyInstance.h"

class PhysicsCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return PhysicsResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};

class ProxyCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return ProxyResource::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);
};


class PhysicsConfigCompiler : public BaseCompiler
{
public:
    virtual std::string getFormatExt() const { return PhysicsConfig::getName(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const JsonValue& root);

    int findFilterIndex(const std::string& name) const;
private:
    std::vector<std::string>    m_filterNames;
};