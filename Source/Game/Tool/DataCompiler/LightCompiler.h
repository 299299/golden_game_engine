#pragma once
#include "BaseCompiler.h"
#include "Light.h"

class LightCompiler : public BaseCompiler
{
public:
    LightCompiler();
    ~LightCompiler();

    virtual std::string getFormatExt() const { return EngineNames::LIGHT; };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
    virtual const void* getCompiledData() const { return &m_light; };
    virtual uint32_t getCompiledDataSize() const { return sizeof(m_light); };

    Light m_light; 
};
