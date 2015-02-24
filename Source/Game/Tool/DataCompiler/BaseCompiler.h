#pragma once
#include "DC_Config.h"

struct ResourceDependency
{
    std::string             m_sourceFile;
    std::string             m_useage;
};

class BaseCompiler
{
public:
    BaseCompiler();
    virtual ~BaseCompiler() {};

    virtual std::string getFormatExt() const { return ""; };
    virtual bool process(const std::string& input, const std::string& output);
    virtual void go();

    virtual void checkDependency();

    virtual void preProcess() {};
    virtual void postProcess();

    virtual bool readJSON(const jsonxx::Object& root);
    virtual BaseCompiler* createChildCompiler(const std::string& type, const jsonxx::Object& root);

    void addDependency(const std::string& useage, const std::string& sourceFile);

    virtual bool checkProcessing();
    virtual bool parseWithJson() const { return false; };

    virtual const void* getCompiledData() const { return 0; };
    virtual uint32_t getCompiledDataSize() const { return 0;};

    std::vector<ResourceDependency>                 m_dependencies;

    std::string                                     m_name;
    std::string                                     m_input;
    std::string                                     m_output;
    std::string                                     m_outputFolder;
    std::string                                     m_pathPrefix;

    int                                             m_mode;
    uint32_t                                        m_modifyTime;
    bool                                            m_processed;
    bool                                            m_subCompilerError;
    bool                                            m_skipped;
};


