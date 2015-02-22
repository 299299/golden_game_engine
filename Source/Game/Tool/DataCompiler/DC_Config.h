#pragma once
#include "ToolUtils.h"

#ifdef _DEBUG
//#define COMPILER_LOAD_TEST
#endif
#define     DC_DATABASE         ("data_compiler_database.txt")
//#define     DC_DUMP_PROFILE

#ifdef DC_DUMP_PROFILE
#define DC_PROFILE(name)      PROFILE(name)
#else
#define DC_PROFILE(name)
#endif

struct ResourceFileDataBase;
class BaseCompiler;
class LevelCompiler;

typedef BaseCompiler* (*__create_compiler__)();
template <class T> BaseCompiler* _create_compiler() { return new T; };
typedef tinystl::unordered_map<uint32_t, __create_compiler__> CompilerBuildMap;

struct DC_Config
{
   DC_Config();
    ~DC_Config();

    ResourceFileDataBase            m_database;
    StringArray                     m_processedShader;
    ToolError                       m_error;
    CompilerBuildMap                m_compilerBuilder;

    std::vector<BaseCompiler*>      m_compilers;
    std::vector<LevelCompiler*>     m_levels;
    std::vector<BaseCompiler*>      m_childCompilers;
    std::vector<BaseCompiler*>      m_processedCompilers;

    std::string                     m_inputDir;
    std::string                     m_inputFile;
    std::string                     m_outputDir;
    std::string                     m_packageName;
    std::string                     m_topFolder;

    bx::LwMutex                     m_childLock;
    int                             m_mode;
    int                             m_numThreads;
    bool                            m_ignoreTextures;
    bool                            m_slient;
    bool                            m_bundled;

    void add_compiler(BaseCompiler* compiler);
    void post_process();
    BaseCompiler* create_compiler(const std::string& ext);
    bool is_engine_ext(const std::string& ext);
    bool is_type_valid(const std::string& type);
};


extern DC_Config* g_config;