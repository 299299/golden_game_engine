#pragma once
#include "BaseCompiler.h"

struct PackageGroup
{
    std::vector<const std::string*>          m_files;
    std::string                              m_ext;
    StringId                                 m_type;
    int                                      m_order;
};

class PackageCompiler : public BaseCompiler
{
public:
    PackageCompiler();
    ~PackageCompiler();

    virtual std::string getFormatExt() const { return "package"; };
    virtual bool process(const std::string& input, const std::string& output);
    virtual void postProcess();

    int findGroup(const std::string& ext) const;
    virtual bool checkProcessing() const { return true; };
    
private:
    std::vector<PackageGroup*>           m_groups;
};
