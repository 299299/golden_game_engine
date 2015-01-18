#include "BaseCompiler.h"
#include "LevelCompiler.h"
#include "ToolUtils.h"
#include "DC_Config.h"

BaseCompiler::BaseCompiler():
m_mode(0),
m_modifyTime(0),
m_processed(false),
m_subCompilerError(false),
m_skipped(false)
{

}

void BaseCompiler::postProcess()
{
    checkDependency();
    if(m_mode != 0 || !m_processed || m_subCompilerError) return;
    g_config->m_database.insertResourceFile(m_input, m_modifyTime);
}

void BaseCompiler::checkDependency()
{
    if(m_dependencies.empty()) return;
    for (size_t i=0; i<m_dependencies.size(); ++i)
    {
        const ResourceDependency& dep = m_dependencies[i];
        if(!isFileExist(dep.m_sourceFile))
        {
            g_config->m_error.add_error("[%s]%s missing %s --> %s", 
                getFormatExt().c_str(), m_input.c_str(), dep.m_useage.c_str(),  dep.m_sourceFile.c_str());
        }
    }
}

void BaseCompiler::addDependency( const std::string& useage, const std::string& sourceFile )
{
    ResourceDependency dep;
    dep.m_useage = useage;
    dep.m_sourceFile = sourceFile;
    m_dependencies.push_back(dep);
}

void BaseCompiler::go()
{
    std::string outputDir = getFilePath(m_output);
    if(!isFolderExist(outputDir)) createFolder(outputDir);
    process(m_input, m_output);
}

bool BaseCompiler::readJSON( const jsonxx::Object& root )
{
    if(m_mode == 0) return true;
    addBackSlash(m_outputFolder);
    m_name = root.get<std::string>("name");
    std::string fileName = getFileName(m_name);
    m_output = m_outputFolder + fileName + "." + getFormatExt();
    return true;
}

extern BaseCompiler* createCompiler(const std::string& ext);
BaseCompiler* BaseCompiler::createChildCompiler( const std::string& type, const jsonxx::Object& root )
{
    BaseCompiler* compiler = createCompiler(type);
    compiler->m_mode = 1;
    compiler->m_outputFolder = getFilePath(m_output);
    if(!compiler->readJSON(root)) m_subCompilerError = true;
    g_config->add_child_compile(compiler);
    return compiler;
}

bool BaseCompiler::checkProcessing()
{
    if(m_mode != 0) return true;
    bool bFileChanged = g_config->m_database.isFileChanged(m_input, m_modifyTime);
    bool bOutputExist = isFileExist(m_output);
    if(bOutputExist && !bFileChanged)
    {
        LOGI("file [%s] not change, ignore.", m_input.c_str())
        m_skipped = true;
        return false;
    }
    return true;
}

bool BaseCompiler::process( const std::string& input, const std::string& output )
{
    std::ifstream ifs(input.c_str());
    if(!ifs.good()) return false;
    jsonxx::Object o;
    if(o.parse(ifs)) return false;
    readJSON(o);
    m_processed = true;
    return true;
}

void BaseCompiler::checkModifyTime()
{
    g_config->m_database.isFileChanged(m_input, m_modifyTime);
}

