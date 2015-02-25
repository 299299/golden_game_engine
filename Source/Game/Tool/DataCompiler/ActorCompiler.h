#pragma once
#include "BaseCompiler.h"
#include "Component.h"

struct ComponentCompilerData
{
    BaseCompiler*           m_compiler;
    ComponentData           m_data;
};

class ActorCompiler : public BaseCompiler
{
public:
    ActorCompiler();
    ~ActorCompiler();

    virtual std::string getFormatExt() const { return EngineNames::ACTOR; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);

    std::vector<ComponentCompilerData>          m_components;
};
