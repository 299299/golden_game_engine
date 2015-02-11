#pragma once
#include "BaseCompiler.h"
#include "Model.h"

class ModelCompiler : public BaseCompiler
{
public:
    ModelCompiler();
    ~ModelCompiler();
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);
    virtual const void* getCompiledData() const { return &m_model; };
    virtual uint32_t getCompiledDataSize() const { return sizeof(m_model); };

    Model m_model; 
};
