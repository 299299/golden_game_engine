#pragma once
#include "stdafx.h"
#include "DC_Utils.h"

struct ResourceDependency
{
    std::string             m_sourceFile;
    std::string             m_useage;
};

class BaseCompiler
{
public:
    BaseCompiler();
    virtual ~BaseCompiler() =0 {};

    virtual std::string getFormatExt() const = 0;
    virtual bool process(const std::string& input, const std::string& output);
    virtual void go();

    virtual void checkDependency();

    virtual void preProcess() {};
    virtual void postProcess();

    virtual bool readJSON(const JsonValue& root);
    virtual BaseCompiler* createChildCompiler(const std::string& type, const JsonValue& root);

    void addDependency(const std::string& useage, const std::string& sourceFile);

    virtual bool checkProcessing();
    virtual bool parseWithJson() const { return false; };
    virtual void checkModifyTime();

    std::string                                     m_name;
    std::string                                     m_input;
    std::string                                     m_output;
    std::string                                     m_outputFolder;
    std::string                                     m_packageName;
    int                                             m_mode;
    uint64_t                                        m_modifyTime;
    std::vector<ResourceDependency>                 m_dependencies;
    bool                                            m_processed;
    bool                                            m_subCompilerError;
    bool                                            m_skipped;
};


