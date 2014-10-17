#include "stdafx.h"
#include "Profiler.h"
#include "DC_Utils.h"
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
#include "ScriptCompiler.h"
#include <bx/tinystl/allocator.h>
#include <bx/tinystl/unordered_map.h>
#include <bx/thread.h>
//=================================================================


DC_Config                               g_config;
ResourceFileDataBase                    g_database;
std::vector<class BaseCompiler*>        g_compilers;
std::vector<class LevelCompiler*>       g_levels;
std::vector<class BaseCompiler*>        g_childCompilers;
static bool                             g_updatePackage = false; 
typedef BaseCompiler* (*__create_compiler__)();
template <class T> BaseCompiler* create_compiler() { return new T; };
typedef tinystl::unordered_map<uint32_t, __create_compiler__> CompilerBuildMap;
CompilerBuildMap                        g_compilerBuilder;

void showHelp()
{
    printf("Usage: DataCompiler input-file [options]\n"
            "it will compile all intermediate asset to data folder.\n"
            "Options:\n"
            "-i input dir (batch mode)\n"
            "-f input file\n"
            "-o output folder\n"
            "-m compile mode default 0\n"
            "-t set num of threads to compile\n"
            "--bundle bundle all resource to package file\n"
            "--slient do not show error msg box\n"
            "--ignore_texture to ignore converting all dds \n"
            "--debug wait for vs debug attach when lunch\n");
}


static const char* g_resourceTypeNames[] = 
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
    ScriptResource::get_name(),
};
static __create_compiler__ g_funtions[] =
{
    create_compiler<AnimationCompiler>,
    create_compiler<AnimRigCompiler>,
    create_compiler<ActorCompiler>,
    create_compiler<LookIKCompiler>,
    create_compiler<ReachIKCompiler>,
    create_compiler<FootIKCompiler>,
    create_compiler<LightCompiler>,
    create_compiler<MaterialCompiler>,
    create_compiler<PhysicsConfigCompiler>,
    create_compiler<PhysicsCompiler>,
    create_compiler<ProxyCompiler>,
    create_compiler<RagdollCompiler>,
    create_compiler<ProgramCompiler>,
    create_compiler<TextureCompiler>,
    create_compiler<Texture3DCompiler>,
    create_compiler<Texture2DCompiler>,
    create_compiler<CopyCompiler>,
    create_compiler<ModelCompiler>,
    create_compiler<ShaderCompiler>,
    create_compiler<ShadingEnviromentCompiler>,
    create_compiler<ShaderIncludeCompiler>,
    create_compiler<DDSCompiler>,
    create_compiler<ScriptCompiler>,
};

void init_factories()
{
    for (int i=0; i<BX_COUNTOF(g_resourceTypeNames); ++i)
    {
        uint32_t key = StringId::calculate(g_resourceTypeNames[i]);
        g_compilerBuilder[key] = g_funtions[i];
    }
}
BaseCompiler* createCompiler(const std::string& ext)
{
    uint32_t key = StringId::calculate(ext.c_str());
    CompilerBuildMap::iterator iter = g_compilerBuilder.find(key);
    if(iter == g_compilerBuilder.end()) return 0;
    return iter->second();
}
bool isEngineExt(const std::string& ext)
{
    uint32_t key = StringId::calculate(ext.c_str());
    CompilerBuildMap::iterator iter = g_compilerBuilder.find(key);
    if(iter == g_compilerBuilder.end()) return false;
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
    uint64_t modifyTime = 0;
    std::vector<std::string> level_file_list;
    std::string folder = remove_top_folder(g_config.m_inputDir);
    bool bTop = folder.empty();
    if(bTop)
    {
        std::vector<std::string> folders;
        findFolders(g_config.m_inputDir, false, folders);
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
        findFiles(g_config.m_inputDir, Level::get_name(), false, level_file_list);
    }
    LOGI("level file num = %d.", level_file_list.size());
    for (size_t i=0; i<level_file_list.size(); ++i)
    {
        const std::string& input = level_file_list[i];
        std::string output = input_to_output(input);
        LevelCompiler* level = new LevelCompiler;
        g_levels.push_back(level);
        bool bFileChanged = g_database.isFileChanged(input, modifyTime);
        bool bFileExist = isFileExist(output);
        if(bFileChanged || !bFileExist) g_updatePackage = true;
        else level->m_skipped = true;
        level->m_input = input;
        level->m_output = output;
        level->m_modifyTime = modifyTime;
        level->m_packageName = get_package_name(input);
        level->preProcess();
        level->go();
    }
}

void resources_process()
{
    std::vector<std::string> input_file_list;
    findFiles(g_config.m_inputDir, "*", true, input_file_list);
    LOGI("input file num = %d.", input_file_list.size());
    bool shaderIncludedAdded = false;

    for (size_t i=0; i<input_file_list.size(); ++i)
    {
        const std::string& input = input_file_list[i];
        std::string ext = getFileExt(input);
        if(ext == Level::get_name()) continue;
        BaseCompiler* compiler = createCompiler(ext);
        if(!compiler) 
        {
            LOGW("can not find any compiler for this resource %s.", input.c_str());
            continue;
        }
        std::string output = input_to_output(input);
        if(ext == "dds") output = replaceExtension(output, Texture::get_name());
        compiler->m_input = input;
        compiler->m_output = output;
        compiler->m_packageName = get_package_name(input);
        if(!compiler->checkProcessing())
        {
            delete compiler;
            continue;
        }
        g_updatePackage = true;
        LOGI("data compile %s --> %s.", input.c_str(), output.c_str());
        g_compilers.push_back(compiler);
    }
    for(size_t i=0; i<g_compilers.size(); ++i)
    {
        g_compilers[i]->preProcess();
    }
}

void singleresource_processing()
{
    uint64_t modifyTime = 0;
    std::string output = input_to_output(g_config.m_inputFile);
    bool bIsOutputExist = isFileExist(output);
    bool bFileChanged = g_database.isFileChanged(g_config.m_inputFile, modifyTime);
    if(bIsOutputExist && !bFileChanged) 
        return;
    std::string inputFileExt = getFileExt(g_config.m_inputFile);
    BaseCompiler* compiler = createCompiler(inputFileExt);
    compiler->m_input = g_config.m_inputFile;
    compiler->m_output = output;
    compiler->m_modifyTime = modifyTime;
    compiler->go();
    g_compilers.push_back(compiler);
    g_updatePackage = true;
    LOGI("single resource process %s --> %s.", compiler->m_input.c_str(), compiler->m_output.c_str());
}

void package_processing()
{
    if(!g_updatePackage) return;

    std::vector<PackageCompiler*> packageCompilers;
    if(g_config.m_packageName.length() > 0)
    {
        PackageCompiler* compiler = new PackageCompiler;
        compiler->m_input = ROOT_DATA_PATH + g_config.m_packageName;
        compiler->m_output = ROOT_DATA_PATH + g_config.m_packageName + ".package";
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

void post_processing()
{
    for(size_t i=0; i<g_compilers.size(); ++i)
    {
        g_compilers[i]->postProcess();
    }
    for(size_t i=0; i<g_childCompilers.size(); ++i)
    {
        g_childCompilers[i]->postProcess();
    }
    for(size_t i=0; i<g_levels.size(); ++i)
    {
        g_levels[i]->postProcess();
    }
    package_processing();
}

void clear_resources()
{
    for(size_t i=0; i<g_compilers.size(); ++i)
    {
        delete g_compilers[i];
    }
    for(size_t i=0; i<g_childCompilers.size(); ++i)
    {
        delete g_childCompilers[i];
    }
    for(size_t i=0; i<g_levels.size(); ++i)
    {
        delete g_levels[i];
    }
    g_levels.clear();
    g_compilers.clear();
    g_childCompilers.clear();
}


int _tmain(int argc, _TCHAR* argv[])
{
    delete_file(DC_ERROR);
    DWORD timeMS = ::GetTickCount();

    if(argc < 2) 
    {
        showHelp();
        printf("argument num < 3 !\n");
        return kErrorArg;
    }

    g_memoryMgr.init(0,0,false,false);
    g_script.init();

    showHelp();
    LOG_INIT("DataCompilerLog.html", MSG_TITLE);
    delete_file(DC_RESULT);
    
    bx::CommandLine cmdline(argc, argv);
    if(cmdline.hasArg("debug"))
    {
        msgBox("wait for visual studio attach process.", MSG_TITLE);
    }
    const char* inputChar = cmdline.findOption('i');
    const char* inputFileChar = cmdline.findOption('f');
    const char* outputFolderChar = cmdline.findOption('o');
    int mode = kDC_DataCompileAndPackageUpdate;
    const char* modeChar = cmdline.findOption('m');
    if(modeChar) mode = atoi(modeChar);
    const char* threadChar = cmdline.findOption('t');
    if(threadChar) g_config.m_numThreads = atoi(threadChar);
    g_config.m_ignoreTextures = cmdline.hasArg("ignore_texture");
    g_config.m_slient = cmdline.hasArg("slient");
    g_config.m_bundled = cmdline.hasArg("bundle");

    if(inputFileChar && outputFolderChar)
    {
        g_config.m_batchMode = false;
    }
    else if(inputChar)
    {
        g_config.m_batchMode = true;
    }
    else if(mode == kDC_PackageUpdateOnly)
    {
        // nothing to do
    }
    else
    {
        addError("arguments error");
        LOG_TERM();
        return kErrorArg;
    }

    init_factories();
    
    if (!isFolderExist("data")) createFolder("data");
    g_database.load(DC_DATABASE);

    if(mode != kDC_PackageUpdateOnly)
    {
        if(g_config.m_batchMode)
        {
            g_config.m_inputDir = inputChar;
            fixPathSlash(g_config.m_inputDir);
            addBackSlash(g_config.m_inputDir);
            g_config.m_topFolder = get_top_folder(g_config.m_inputDir);
            g_config.m_outputDir = input_to_output(g_config.m_inputDir);
        }
        else
        {
            LOGD("input as a single file --> %s", inputFileChar);
            g_config.m_inputFile = inputFileChar;
            fixPathSlash(g_config.m_inputFile);
            g_config.m_inputDir = getFilePath(g_config.m_inputFile);
            g_config.m_outputDir = outputFolderChar;
            addBackSlash(g_config.m_inputDir);
            g_config.m_topFolder = get_top_folder(g_config.m_inputDir);
            
        }
        ENGINE_ASSERT(g_config.m_topFolder.length(), "top folder error.");
        fixPathSlash(g_config.m_outputDir);
        addBackSlash(g_config.m_outputDir);
        std::string secondFolder = remove_top_folder(g_config.m_outputDir);
        if(secondFolder.length()) g_config.m_packageName = get_top_folder(secondFolder);
        LOGI("input = %s, output = %s, top-folder = %s, package-name=%s, batch=%d", 
                g_config.m_inputDir.c_str(), 
                g_config.m_outputDir.c_str(), 
                g_config.m_topFolder.c_str(),
                g_config.m_packageName.c_str(),
                g_config.m_batchMode);
    }

    if(mode == kDC_PackageUpdateOnly)
    {
        package_processing();
    }
    else if(!g_config.m_batchMode)
    {
        singleresource_processing();
        post_processing();
    }
    else
    {
        level_processing();
        resources_process();
        if(g_compilers.size() < 10) g_config.m_numThreads = 0;
        if(g_config.m_numThreads < 2)
        {
            for(size_t i=0; i<g_compilers.size(); ++i)
            {
                g_compilers[i]->go();
            }
        }
        else
        {
            const int maxThreads = 8;
            if(g_config.m_numThreads > maxThreads) g_config.m_numThreads = maxThreads;
            uint32_t totalNum = g_compilers.size();
            uint32_t numPerThread = totalNum / g_config.m_numThreads + 1;
            bx::Thread* threads[maxThreads];
            std::vector<BaseCompiler*> compilers[maxThreads];
            uint32_t currIndex = 0;

            for (int i=0; i<g_config.m_numThreads; ++i)
            {
                uint32_t elementNum = numPerThread;
                uint32_t numLeft = totalNum - currIndex;
                if(numLeft < elementNum) elementNum = numLeft;
                if(elementNum == 0) continue;
                std::vector<BaseCompiler*>& comArray = compilers[i];
                comArray.resize(elementNum);
                memcpy(&comArray[0], &g_compilers[currIndex], elementNum*sizeof(BaseCompiler*));
                currIndex += elementNum;
                if(i == 0) continue;
                threads[i] = new bx::Thread();
                threads[i]->init(thread_compile, &comArray);
            }
            //main thread with other threads.
            thread_compile(&compilers[0]);

            for (int i=1; i<g_config.m_numThreads; ++i)
            {
                delete threads[i];
            }
            
        }
        post_processing();
    }

    timeMS = ::GetTickCount() - timeMS;
    
    extern int g_errorNum;
    g_config.m_exitCode = -g_errorNum;
    showErrorMessage(MSG_TITLE, DC_ERROR, g_config.m_slient);

    if(g_compilers.size() < 20) saveCompileResult(DC_RESULT);
    g_database.save(DC_DATABASE);
    clear_resources();
    g_database.m_files.clear();
    g_compilerBuilder.clear();
    g_script.quit();
    g_memoryMgr.quit();

    g_profiler.dump_to_file("datacompiler_profile.txt", true, true);

    LOGD("******************************************************");
    LOGD("******************************************************");
    LOGD("* TOTAL TIME COST = %d[MS] *", timeMS);
    LOGD("******************************************************");
    LOGD("******************************************************");
    LOG_TERM();
	return g_config.m_exitCode;
}

