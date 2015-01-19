#include "Profiler.h"
#include "ToolUtils.h"
#include "DC_Config.h"
#include "Mesh.h"
//=================================================================
#include "AnimationCompiler.h"
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
        Animation::get_name(),
        AnimRig::get_name(),
        ActorResource::get_name(),
        LookAtResource::get_name(),
        ReachResource::get_name(),
        FootResource::get_name(),
        LightResource::get_name(),
        Material::get_name(),
        PhysicsConfig::get_name(),
        PhysicsResource::get_name(),
        ProxyResource::get_name(),
        RagdollResource::get_name(),
        ShaderProgram::get_name(),
        Texture::get_name(),
        Raw3DTexture::get_name(),
        Raw2DTexture::get_name(),
        Mesh::get_name(),
        ModelResource::get_name(),
        Shader::get_name(),
        ShadingEnviroment::get_name(),
        SHADER_INCLUDE_EXT,
        "dds",
    };
    __create_compiler__ g_funtions[] =
    {
        _create_compiler<AnimationCompiler>,
        _create_compiler<AnimRigCompiler>,
        _create_compiler<ActorCompiler>,
        _create_compiler<LookIKCompiler>,
        _create_compiler<ReachIKCompiler>,
        _create_compiler<FootIKCompiler>,
        _create_compiler<LightCompiler>,
        _create_compiler<MaterialCompiler>,
        _create_compiler<PhysicsConfigCompiler>,
        _create_compiler<PhysicsCompiler>,
        _create_compiler<ProxyCompiler>,
        _create_compiler<RagdollCompiler>,
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
        m_compilerBuilder[StringId::calculate(g_resourceTypeNames[i])] = g_funtions[i];
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
}

BaseCompiler* DC_Config::create_compiler( const std::string& ext )
{
    uint32_t key = StringId::calculate(ext.c_str());
    CompilerBuildMap::iterator iter = m_compilerBuilder.find(key);
    if(iter == m_compilerBuilder.end()) return 0;
    return iter->second();
}

bool DC_Config::is_engine_ext( const std::string& ext )
{
    uint32_t key = StringId::calculate(ext.c_str());
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
    std::vector<std::string> level_file_list;
    std::string folder = remove_top_folder(g_config->m_inputDir);
    bool bTop = folder.empty();
    if(bTop)
    {
        std::vector<std::string> folders;
        findFolders(g_config->m_inputDir, false, folders);
        for (size_t i=0; i<folders.size();++i)
        {
            std::vector<std::string> levelFiles;
            addBackSlash(folders[i]);
            findFiles(folders[i], Level::get_name(), false, levelFiles);
            for (size_t j=0; j<levelFiles.size(); ++j)
            {
                level_file_list.push_back(levelFiles[j]);
            }
        }
    }
    else
    {
        findFiles(g_config->m_inputDir, Level::get_name(), false, level_file_list);
    }
    LOGI("level file num = %d.", level_file_list.size());
    for (size_t i=0; i<level_file_list.size(); ++i)
    {
        const std::string& input = level_file_list[i];
        std::string output = input_to_output(input);
        LevelCompiler* level = new LevelCompiler;
        g_config->m_levels.push_back(level);
        bool bFileChanged = g_config->m_database.isFileChanged(input, modifyTime);
        bool bFileExist = isFileExist(output);
        if(bFileChanged || !bFileExist) {}
        else level->m_skipped = true;
        level->m_input = input;
        level->m_output = output;
        level->m_modifyTime = modifyTime;
        level->preProcess();
        level->go();
    }
}

void resources_process()
{
    std::vector<std::string> input_file_list;
    findFiles(g_config->m_inputDir, "*", true, input_file_list);
    LOGI("input file num = %d.", input_file_list.size());
    bool shaderIncludedAdded = false;

    for (size_t i=0; i<input_file_list.size(); ++i)
    {
        const std::string& input = input_file_list[i];
        std::string ext = getFileExt(input);
        if(ext == Level::get_name()) continue;
        BaseCompiler* compiler = g_config->create_compiler(ext);
        if(!compiler)
        {
            LOGW("can not find any compiler for this resource %s.", input.c_str());
            continue;
        }
        std::string output = input_to_output(input);
        if(ext == "dds") output = replaceExtension(output, Texture::get_name());
        compiler->m_input = input;
        compiler->m_output = output;
        if(!compiler->checkProcessing())
        {
            delete compiler;
            continue;
        }
        LOGI("data compile %s --> %s.", input.c_str(), output.c_str());
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
        addBackSlash(compiler->m_input);
        LOGI("package compile %s -> %s", compiler->m_input.c_str(), compiler->m_output.c_str());
        packageCompilers.push_back(compiler);
    }
    else
    {
        std::vector<std::string> folders;
        findFolders(ROOT_DATA_PATH, false, folders);
        for(size_t i=0; i<folders.size(); ++i)
        {
            std::string folder = remove_top_folder(folders[i]);
            PackageCompiler* compiler = new PackageCompiler;
            compiler->m_input = ROOT_DATA_PATH + folder;
            compiler->m_output = ROOT_DATA_PATH + folder + ".package";
            addBackSlash(compiler->m_input);
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
    int err = kErrorSuccess;
    uint32_t timeMS = ::GetTickCount();
    if(argc < 2)
    {
        printf("argument num < 3 !\n");
        return kErrorArg;
    }

    g_config = new DC_Config;
    MemoryConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    g_memoryMgr.init(cfg);

    LOG_INIT("DataCompilerLog.html", "DataCompiler");

    const char* inputChar = cmdline->findOption('i');
    const char* inputFileChar = cmdline->findOption('f');
    const char* outputFolderChar = cmdline->findOption('o');
    const char* threadChar = cmdline->findOption('t');
    if(threadChar) g_config->m_numThreads = atoi(threadChar);
    g_config->m_ignoreTextures = cmdline->hasArg("ignore_texture");
    g_config->m_slient = cmdline->hasArg("slient");
    g_config->m_bundled = cmdline->hasArg("bundle");

    createFolder("data");
    g_config->m_database.load(DC_DATABASE);

    g_config->m_inputDir = inputChar;
    fixPathSlash(g_config->m_inputDir);
    addBackSlash(g_config->m_inputDir);
    g_config->m_topFolder = get_top_folder(g_config->m_inputDir);
    g_config->m_outputDir = input_to_output(g_config->m_inputDir);

    ENGINE_ASSERT(g_config->m_topFolder.length(), "top folder error.");
    fixPathSlash(g_config->m_outputDir);
    addBackSlash(g_config->m_outputDir);
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
    g_memoryMgr.shutdown();

    g_profiler.dump_to_file("datacompiler_profile.txt", true, true);

    LOGD("******************************************************");
    LOGD("******************************************************");
    LOGD("* TOTAL TIME COST = %d[MS] *", timeMS);
    LOGD("******************************************************");
    LOGD("******************************************************");
    LOG_TERM();

	return err;
}

