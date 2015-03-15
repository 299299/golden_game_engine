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
    if(!m_processed || m_subCompilerError || m_skipped) 
        return;
    g_config->m_processedCompilers.push_back(this);
    if(m_mode != 0)
        return;
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
    LOGD("[%s] processing from %s to %s", getFormatExt().c_str(), m_input.c_str(), m_output.c_str());
    std::string outputDir = getFilePath(m_output);
    create_folder(outputDir);
    process(m_input, m_output);
    //LOGD("finished processing");
}

bool BaseCompiler::readJSON( const jsonxx::Object& root )
{
    if(m_mode == 0) 
        return true;
    add_trailing_slash(m_outputFolder);
    m_name = root.get<std::string>("name");
    std::string fileName = getFileName(m_name);
    m_output = m_outputFolder + fileName + "." + getFormatExt();
    return true;
}

BaseCompiler* BaseCompiler::createChildCompiler( const std::string& type, const jsonxx::Object& root )
{
    BaseCompiler* compiler = g_config->create_compiler(type);
    if(!compiler) 
        return 0;
    compiler->m_mode = 1;
    compiler->m_outputFolder = getFilePath(m_output);
    compiler->m_pathPrefix = m_pathPrefix;
    bool _ok = compiler->readJSON(root);
    if(!_ok) 
        m_subCompilerError = true;
    compiler->m_processed = _ok;
    g_config->add_compiler(compiler);
    return compiler;
}

bool BaseCompiler::checkProcessing()
{
    if(m_mode != 0) return true;
    bool bFileChanged = g_config->is_file_changed(m_input, m_modifyTime);
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
    ENGINE_ASSERT(parseWithJson(), "NOT A JSON PARSER COMPILER!");
    if(m_processed)
        return true;
    jsonxx::Object o;
    m_processed = read_json_from_file(o, input);
    if(!m_processed)
    {
        g_config->m_error.add_error("%s error %s", __FUNCTION__, input.c_str());
        return false;
    }
    return m_processed = readJSON(o);
}