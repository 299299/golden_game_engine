#pragma once
#include "BaseCompiler.h"
#include "Component.h"

class ActorCompiler : public BaseCompiler
{
public:
    ActorCompiler();
    ~ActorCompiler();

    virtual std::string getFormatExt() const { return EngineNames::ACTOR; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);

    std::vector<BaseCompiler*>          m_components;
    std::vector<ComponentData>          m_components_data;

};
