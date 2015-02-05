#include "Profiler.h"
#include "ToolUtils.h"
#include "DC_Config.h"
#include "Mesh.h"
//=================================================================
#include "AnimationCompiler.h"
#include "AnimationStateCompiler.h"
#include "AnimRigCompiler.h"
#include "ActorCompiler.h"
#include "IKCompiler.h"
#include "LightCompiler.h"
#include "MaterialCompiler.h"
#include "PhysicsCompiler.h"
#include "RagdollCompiler.h"
#include "ShaderCompiler.h"
#include "TextureCompiler.h"
#include "PackageCompiler.h"
#include "CopyCompiler.h"
#include "ModelCompiler.h"
#include "ShadingEnviromentCompiler.h"
#include "LevelCompiler.h"
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
#include <bx/thread.h>
//=================================================================

DC_Config* g_config = NULL;

DC_Config::DC_Config()
:m_mode(0)
,m_numThreads(0)
,m_ignoreTextures(false) //--> for speed up data compile
,m_slient(false)
,m_bundled(false)
{
    const char* g_resourceTypeNames[] =
    {
        EngineNames::ANIMATION,
        EngineNames::ANIMATION_STATES,
        EngineNames::ANIMATION_RIG,
        EngineNames::ACTOR,
        EngineNames::LIGHT,
        EngineNames::MATERIAL,
        EngineNames::PHYSICS_CONFIG,
        EngineNames::PROGRAM,
        EngineNames::TEXTURE,
        EngineNames::TEXTURE_3D,
        EngineNames::TEXTURE_2D,
        EngineNames::MESH,
        EngineNames::MODEL,
        EngineNames::SHADER,
        EngineNames::SHADING_ENV,
        SHADER_INCLUDE_EXT,
        "dds",
    };
    __create_compiler__ g_funtions[] =
    {
        _create_compiler<AnimationCompiler>,
        _create_compiler<AnimationStateCompiler>,
        _create_compiler<AnimRigCompiler>,
        _create_compiler<ActorCompiler>,
        _create_compiler<LightCompiler>,
        _create_compiler<MaterialCompiler>,
        _create_compiler<PhysicsConfigCompiler>,
        _create_compiler<ProgramCompiler>,
        _create_compiler<TextureCompiler>,
        _create_compiler<Texture3DCompiler>,
        _create_compiler<Texture2DCompiler>,
        _create_compiler<CopyCompiler>,
        _create_compiler<ModelCompiler>,
        _create_compiler<ShaderCompiler>,
        _create_compiler<ShadingEnviromentCompiler>,
        _create_compiler<ShaderIncludeCompiler>,
        _create_compiler<DDSCompiler>,
    };

    uint32_t num = BX_COUNTOF(g_resourceTypeNames);
    for (uint32_t i=0; i<num; ++i)
    {
        m_compilerBuilder[stringid_caculate(g_resourceTypeNames[i])] = g_funtions[i];
    }
}

DC_Config::~DC_Config()
{
    for(size_t i=0; i<m_compilers.size(); ++i)
    {
        delete m_compilers[i];
    }
    for(size_t i=0; i<m_childCompilers.size(); ++i)
    {
        delete m_childCompilers[i];
    }
    for(size_t i=0; i<m_levels.size(); ++i)
    {
        delete m_levels[i];
    }
    m_levels.clear();
    m_compilers.clear();
    m_childCompilers.clear();
}

void DC_Config::add_child_compile( BaseCompiler* compiler )
{
    bx::LwMutexScope _l(m_childLock);
    m_childCompilers.push_back(compiler);
}

static int compare_less_resource(const std::string& nameA, const std::string& nameB)
{
    extern int get_resource_order(const char*);
    int orderA = get_resource_order(getFileExt(nameA).c_str());
    int orderB = get_resource_order(getFileExt(nameB).c_str());
    return orderA < orderB;
}

void DC_Config::post_process()
{
    for(size_t i=0; i<m_compilers.size(); ++i)
    {
        m_compilers[i]->postProcess();
    }
    for(size_t i=0; i<m_childCompilers.size(); ++i)
    {
        m_childCompilers[i]->postProcess();
    }
    for(size_t i=0; i<m_levels.size(); ++i)
    {
        m_levels[i]->postProcess();
    }

    std::ofstream ofs(DC_RESULT);
    if(!ofs.good())
        return;
    ofs.clear();

    StringArray _results;
    _results.resize(m_processedCompilers.size());
    for(size_t i=0; i<_results.size(); ++i)
    {
        _results[i] = m_processedCompilers[i]->m_output;
    }

    std::sort(_results.begin(), _results.end(), compare_less_resource);

    for(size_t i=0; i<_results.size(); ++i)
    {
        LOGD("---> processed ---> %s", _results[i].c_str());
        ofs << _results[i] << std::endl;
    }
}

BaseCompiler* DC_Config::create_compiler( const std::string& ext )
{
    //LOGD("create compiler key = %s", ext.c_str());
    uint32_t key = stringid_caculate(ext.c_str());
    CompilerBuildMap::iterator iter = m_compilerBuilder.find(key);
    if(iter == m_compilerBuilder.end()) return 0;
    return iter->second();
}

bool DC_Config::is_type_valid( const std::string& type )
{
    uint32_t key = stringid_caculate(type.c_str());
    return m_compilerBuilder.find(key) != m_compilerBuilder.end();
}

bool DC_Config::is_engine_ext( const std::string& ext )
{
    uint32_t key = stringid_caculate(ext.c_str());
    CompilerBuildMap::iterator iter = m_compilerBuilder.find(key);
    if(iter == m_compilerBuilder.end()) return false;
    return true;
}

int32_t thread_compile(void* _userData)
{
    std::vector<BaseCompiler*>* compilers = (std::vector<BaseCompiler*>*)(_userData);
    for (size_t i=0; i<compilers->size(); ++i)
    {
        BaseCompiler* c = compilers->operator [](i);
        c->go();
    }
    return 0;
}

void level_processing()
{
    uint32_t modifyTime = 0;
    StringArray level_file_list;
    std::string folder = remove_top_folder(g_config->m_inputDir);
    scan_dir(level_file_list, g_config->m_inputDir.c_str(), EngineNames::LEVEL, SCAN_FILES, true);

    LOGI("level file num = %d", level_file_list.size());
    for (size_t i=0; i<level_file_list.size(); ++i)
    {
        LOGI("level %s", level_file_list[i].c_str());
    }

    for (size_t i=0; i<level_file_list.size(); ++i)
    {
        const std::string& input = level_file_list[i];
        std::string output = input_to_output(input);
        LevelCompiler* level = new LevelCompiler;
        g_config->m_levels.push_back(level);
        if(!g_config->m_database.isFileChanged(input, modifyTime) && isFileExist(output))
            level->m_skipped = true;
        level->m_input = input;
        level->m_output = output;
        level->m_modifyTime = modifyTime;
        level->preProcess();
        level->go();
    }
}

void resources_process()
{
    StringArray input_file_list;
    scan_dir(input_file_list, g_config->m_inputDir.c_str(), "*", SCAN_FILES, true);

    LOGI("input file num = %d.", input_file_list.size());
    bool shaderIncludedAdded = false;

    for (size_t i=0; i<input_file_list.size(); ++i)
    {
        const std::string& input = input_file_list[i];
        std::string ext = getFileExt(input);
        if(ext == EngineNames::LEVEL) continue;
        BaseCompiler* compiler = g_config->create_compiler(ext);
        if(!compiler)
        {
            LOGW("can not find any compiler for this resource %s.", input.c_str());
            continue;
        }
        std::string output = input_to_output(input);
        if(ext == "dds") output = replaceExtension(output, EngineNames::TEXTURE);
        compiler->m_input = input;
        compiler->m_output = output;
        if(!compiler->checkProcessing())
        {
            delete compiler;
            continue;
        }
        LOGI("data compile %s --> %s", input.c_str(), output.c_str());
        g_config->m_compilers.push_back(compiler);
    }
    for(size_t i=0; i<g_config->m_compilers.size(); ++i)
    {
        g_config->m_compilers[i]->preProcess();
    }
}

void package_processing()
{
    std::vector<PackageCompiler*> packageCompilers;
    if(g_config->m_packageName.length() > 0)
    {
        PackageCompiler* compiler = new PackageCompiler;
        compiler->m_input = ROOT_DATA_PATH + g_config->m_packageName;
        compiler->m_output = ROOT_DATA_PATH + g_config->m_packageName + ".package";
        add_trailing_slash(compiler->m_input);
        LOGI("package compile %s -> %s", compiler->m_input.c_str(), compiler->m_output.c_str());
        packageCompilers.push_back(compiler);
    }
    else
    {
        StringArray folders;
        scan_dir(folders, ROOT_DATA_PATH, "*", SCAN_DIRS, false);
        for(size_t i=0; i<folders.size(); ++i)
        {
            std::string folder = remove_top_folder(folders[i]);
            PackageCompiler* compiler = new PackageCompiler;
            compiler->m_input = ROOT_DATA_PATH + folder;
            compiler->m_output = ROOT_DATA_PATH + folder + ".package";
            add_trailing_slash(compiler->m_input);
            LOGI("package compile %s -> %s", compiler->m_input.c_str(), compiler->m_output.c_str());
            packageCompilers.push_back(compiler);
        }
    }
    for(size_t i=0; i<packageCompilers.size(); ++i)
    {
        packageCompilers[i]->preProcess();
    }
    for(size_t i=0; i<packageCompilers.size(); ++i)
    {
        packageCompilers[i]->go();
    }
    for(size_t i=0; i<packageCompilers.size(); ++i)
    {
        packageCompilers[i]->postProcess();
    }
    for(size_t i=0; i<packageCompilers.size(); ++i)
    {
        delete packageCompilers[i];
    }
    packageCompilers.clear();
}

int data_compiler_main(int argc, bx::CommandLine* cmdline)
{
    delete_file(DC_RESULT);

    int err = kErrorSuccess;
    uint32_t timeMS = ::GetTickCount();

    LOG_INIT("DataCompilerLog.html", "Data Compiler");
    MemoryConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    cfg.m_debugMemSize = DEBUG_MEMORY_SIZE;
    g_memoryMgr.init(cfg);

#ifdef DC_DUMP_PROFILE
    g_profiler.init(TOTAL_BLOCK_NUM);
#endif

    g_config = new DC_Config;
    const char* inputChar = cmdline->findOption('i');
    if(!inputChar) inputChar = "intermediate";
    const char* outputFolderChar = cmdline->findOption('o');
    if(!outputFolderChar) outputFolderChar = "data";
    const char* threadChar = cmdline->findOption('t');
    if(threadChar) g_config->m_numThreads = atoi(threadChar);
    g_config->m_ignoreTextures = cmdline->hasArg("ignore_texture");
    g_config->m_slient = cmdline->hasArg("slient");
    g_config->m_bundled = cmdline->hasArg("bundle");

    create_folder("data");
    g_config->m_database.load(DC_DATABASE);

    g_config->m_inputDir = inputChar;
    string_replace(g_config->m_inputDir, "\\", "/");
    add_trailing_slash(g_config->m_inputDir);
    g_config->m_topFolder = get_top_folder(g_config->m_inputDir);
    g_config->m_outputDir = input_to_output(g_config->m_inputDir);

    ENGINE_ASSERT(g_config->m_topFolder.length(), "top folder error.");
    string_replace(g_config->m_outputDir, "\\", "/");
    add_trailing_slash(g_config->m_outputDir);
    std::string secondFolder = remove_top_folder(g_config->m_outputDir);
    if(secondFolder.length()) g_config->m_packageName = get_top_folder(secondFolder);
    LOGI("input = %s, output = %s, top-folder = %s, package-name=%s",
        g_config->m_inputDir.c_str(),
        g_config->m_outputDir.c_str(),
        g_config->m_topFolder.c_str(),
        g_config->m_packageName.c_str());

    level_processing();
    resources_process();
    if(g_config->m_compilers.size() < 10) g_config->m_numThreads = 0;
    if(g_config->m_numThreads < 2)
    {
        for(size_t i=0; i<g_config->m_compilers.size(); ++i)
        {
            g_config->m_compilers[i]->go();
        }
    }
    else
    {
        const int maxThreads = 8;
        if(g_config->m_numThreads > maxThreads) g_config->m_numThreads = maxThreads;
        uint32_t totalNum = g_config->m_compilers.size();
        uint32_t numPerThread = totalNum / g_config->m_numThreads + 1;
        bx::Thread* threads[maxThreads];
        std::vector<BaseCompiler*> compilers[maxThreads];
        uint32_t currIndex = 0;

        for (int i=0; i<g_config->m_numThreads; ++i)
        {
            uint32_t elementNum = numPerThread;
            uint32_t numLeft = totalNum - currIndex;
            if(numLeft < elementNum) elementNum = numLeft;
            if(elementNum == 0) continue;
            std::vector<BaseCompiler*>& comArray = compilers[i];
            comArray.resize(elementNum);
            memcpy(&comArray[0], &g_config->m_compilers[currIndex], elementNum*sizeof(void*));
            currIndex += elementNum;
            if(i == 0) continue;
            threads[i] = new bx::Thread();
            threads[i]->init(thread_compile, &comArray);
        }
        //main thread with other threads.
        thread_compile(&compilers[0]);
        for (int i=1; i<g_config->m_numThreads; ++i)
        {
            delete threads[i];
        }
    }
    g_config->post_process();
    package_processing();

    timeMS = ::GetTickCount() - timeMS;
    if(!g_config->m_slient) g_config->m_error.show_error();
    g_config->m_database.save(DC_DATABASE);
    g_config->m_database.m_files.clear();
    SAFE_DELETE(g_config);

#ifdef DC_DUMP_PROFILE
    g_profiler.dump_to_file("data_compiler_profile.txt", true, true);
    g_profiler.shutdown();
#endif

    g_memoryMgr.shutdown();

    LOGD("******************************************************");
    LOGD("******************************************************");
    LOGD("* TOTAL TIME COST = %d[MS] *", timeMS);
    LOGD("******************************************************");
    LOGD("******************************************************");
    LOG_TERM();

	return err;
}

