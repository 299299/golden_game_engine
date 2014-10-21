#include "stdafx.h"
#include "Profiler.h"
#include "CharacterConverter.h"
#include "StaticModelConverter.h"
#include "LevelConverter.h"
#include "AnimationConverter.h"
#include "linear_allocator.h"
#include "HC_Utils.h"
#include <bx/thread.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Thread/Thread/hkWorkerThreadContext.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

#define HAVOK_DATABASE ("havok_convert_database.txt")

struct HavokThreadContext
{
    std::vector<Actor_Config*>          m_files;
    int                                 m_threadId;
};

HAVOK_Config                            g_config;
static  std::vector<Actor_Config*>      g_havokFiles;
ResourceFileDataBase                    g_havokDB;

void showHelp()
{
    printf("Usage: HavokConverter [options]\n"
            "it will convert havok file format to intermediate json format.\n"
            "Options:\n"
            "-f  specific input hkx file\n"
            "-o  specific convert output folder\n"
            "-i  specific input folder for batch export \n"
            "-t set num of threads to compile\n"
            "--slient do not show error msg box\n"
            "--packnormal pack normal\n"
            "--packuv pack uv\n"
            "--debug to wait for vs debug attach when lunch\n");
}
void havok_convert(Actor_Config* config)
{
    LOGI("havok convert %s ---> %s", config->m_input.c_str(), config->m_output.c_str());
    config->m_loader = new hkLoader;
    hkRootLevelContainer* rlc = config->m_loader->load(config->m_input.c_str());
    if (!rlc)
    {
        addError("can not load input havok file %s", config->m_input.c_str());
        g_config.m_exitCode = kExitHavokLoadError;
        SAFE_REMOVEREF(config->m_loader);
        return;
    }

    config->m_rlc = rlc;
    if(!isFolderExist(config->m_exportFolder)) createFolder(config->m_exportFolder);
    hkxEnvironment* env = LOAD_OBJECT(rlc, hkxEnvironment);
    if(env)
    {
        hkStringBuf env_str;
        env->convertToString(env_str);
        LOGI(env_str.cString());
        for(int i=0; i<env->getNumVariables(); ++i)
        {
            const char* name = env->getVariableName(i);
            if(!strcmp(name,"WORK_SPACE")) config->m_workspaceFolder = env->getVariableValue(i);
            if(!strcmp(name,"EXPORT_MODE")) config->m_exportMode = env->getVariableValue(i);
        }
        config->m_assetFolder = env->getVariableValue("assetFolder");
        config->m_assetPath = env->getVariableValue("assetPath");
    }

    hkaAnimationContainer* ac = LOAD_OBJECT(rlc, hkaAnimationContainer);
    hkxScene* scene = LOAD_OBJECT(rlc,hkxScene);
    hkpPhysicsData* data = LOAD_OBJECT(rlc, hkpPhysicsData);

    config->m_scene = scene;
    config->m_animation = ac;
    config->m_physics = data;

    ActorConverter* converter = 0;
    if(config->m_exportMode == "model")
    {
        if(!scene || !scene->m_rootNode)
        {
            SAFE_REMOVEREF(config->m_loader);
            return;
        }
        converter = new StaticModelConverter;
        converter->setClass(config->m_exportClass);
    }
    else if(config->m_exportMode == "skinning")
    {
        converter = new CharacterConverter;
        converter->setClass("character");
    }
    else if(config->m_exportMode == "level")
    {
        converter = new LevelConverter;
    }
    else if(config->m_exportMode == "animation")
    {
        converter = new AnimationConverter;
        config->m_output = config->m_exportFolder + config->m_exportName + "." + Animation::get_name();
    }
    if(!converter)
    {
        SAFE_REMOVEREF(config->m_loader);
        return;
    }

    converter->m_config = config;
    converter->setName(config->m_exportName);
    if(config->m_exportMode == "skinning") converter->process(ac);
    else if(config->m_exportMode == "animation") converter->process(ac);
    else converter->process(scene);
    converter->postProcess();
    converter->serializeToFile(config->m_output.c_str());

    SAFE_REMOVEREF(converter);
    SAFE_REMOVEREF(config->m_loader);
}

void pre_process()
{
    std::string inputFolderName(g_config.m_inputDir);
    fixPathSlash(inputFolderName);
    addBackSlash(inputFolderName);
    std::vector<std::string> hkxFolders;
    findFolders(inputFolderName, false, hkxFolders);
    uint64_t fileTime = 0;

    for (size_t i=0; i<hkxFolders.size();++i)
    {
        std::string folderName = hkxFolders[i];
        fixPathSlash(folderName);
        int index = folderName.find_last_of('/') + 1;
        std::string packageName = folderName.substr(index, folderName.length() - index);
        std::vector<std::string> hkxFiles;
        std::string findFolder = folderName;
        addBackSlash(findFolder);
        findFiles(findFolder, "hkx", true, hkxFiles);
        std::string outFolder = std::string(INTERMEDIATE_PATH) + packageName + "/";
        for (size_t i=0; i<hkxFiles.size(); ++i)
        {
            Actor_Config* config = createConfig(hkxFiles[i], outFolder);
            if(config) g_havokFiles.push_back(config);
        }
    }
}

void post_process()
{
    for(size_t i=0; i<g_havokFiles.size(); ++i)
    {
        const Actor_Config* file = g_havokFiles[i];
        g_havokDB.insertResourceFile(file->m_input, file->m_time);
        delete file;
    }
    g_havokFiles.clear();
}

int32_t thread_compile(void* _userData)
{
    HavokThreadContext* data = (HavokThreadContext*)_userData;
    hkWorkerThreadContext context(data->m_threadId);
    for(size_t i=0; i<data->m_files.size(); ++i)
    {
        havok_convert(data->m_files[i]);
    }
    return 0;
}


int main(int argc, char* argv[])
{
    delete_file(HAVOK_ERROR);
    DWORD timeMS = ::GetTickCount();
    //======================================================
#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
    // Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
    // Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif
    //=======================================================

    const int numMinArgs = 3;
    if(argc < numMinArgs)
    {
        printf("argnum less than %d\n", numMinArgs);
        showHelp();
        return kExitErrorArg;
    }

    showHelp();
    LOG_INIT("HavokConverterLog.html", MSG_TITLE);
    g_memoryMgr.init(1024,1024,true,true);

    bx::CommandLine cmdline(argc, argv);
    if(cmdline.hasArg("debug"))
    {
        msgBox("wait for visual studio attach process.", MSG_TITLE);
    }

    g_config.m_packNormal = cmdline.hasArg("packnormal");
    g_config.m_packUV = cmdline.hasArg("packuv");
    g_config.m_slient = cmdline.hasArg("slient"); 
	const char* outputDir = cmdline.findOption('o');
	if(outputDir) g_config.m_outputDir = outputDir;

    const char* threadChar = cmdline.findOption('t');
    if(threadChar) g_config.m_numThreads = atoi(threadChar);

    const char* inputFolder = cmdline.findOption('i');
    if (inputFolder)
    {
        g_config.m_batchMode = true;
        g_config.m_inputDir = inputFolder;
        g_havokDB.load(HAVOK_DATABASE);
        pre_process();
        if(g_havokFiles.size() < 10) g_config.m_numThreads = 0;
        if(g_config.m_numThreads < 2)
        {
            for(size_t i=0; i<g_havokFiles.size(); ++i)
            {
                havok_convert(g_havokFiles[i]);
            }
        }
        else
        {
            const int maxThreads = 8;
            if(g_config.m_numThreads > maxThreads) g_config.m_numThreads = maxThreads;
            uint32_t totalNum = g_havokFiles.size();
            uint32_t numPerThread = totalNum / g_config.m_numThreads;
            bx::Thread* threads[maxThreads];
            HavokThreadContext contexts[maxThreads];
            uint32_t currIndex = 0;

            for (int i=0; i<g_config.m_numThreads; ++i)
            {
                uint32_t elementNum = numPerThread;
                uint32_t numLeft = totalNum - currIndex;
                if(numLeft < elementNum) elementNum = numLeft;
                if(elementNum == 0) continue;
                HavokThreadContext& contex = contexts[i];
                contex.m_threadId = i;
                contex.m_files.resize(elementNum);
                memcpy(&contex.m_files[0], &g_havokFiles[currIndex], elementNum*sizeof(Actor_Config*));
                currIndex += elementNum;
                if(i == 0) continue;
                threads[i] = new bx::Thread();
                threads[i]->init(thread_compile, &contex);
            }

            HavokThreadContext& contex0 = contexts[0];
            for(size_t i=0; i<contex0.m_files.size(); ++i)
            {
                havok_convert(contex0.m_files[i]);
            }
            for (int i=1; i<g_config.m_numThreads; ++i)
            {
                delete threads[i];
            }
        }
        post_process();
        g_havokDB.save(HAVOK_DATABASE);
    }
    else
    {
        Actor_Config config;
        const char* input = cmdline.findOption('f');
        const char* output = cmdline.findOption('o');
        if(input && output) 
        {
            Actor_Config* cfg = createConfig(input, output);
            if(cfg) havok_convert(cfg);
            delete cfg;
        }
        else addError("single havok convert must specific f & o args!");
    }

    extern int g_errorNum;
    g_config.m_exitCode = -g_errorNum;
    showErrorMessage(MSG_TITLE, HAVOK_ERROR, g_config.m_slient);

    g_memoryMgr.quit();

    g_profiler.dump_to_file("havokconverter_profile.txt", true, true);

    timeMS = ::GetTickCount() - timeMS;
    LOGD("******************************************************");
    LOGD("******************************************************");
    LOGD("* TOTAL TIME COST = %d[MS] RET CODE = %d *", timeMS, g_config.m_exitCode);
    LOGD("******************************************************");
    LOGD("******************************************************");

    LOG_TERM();
	return g_config.m_exitCode;
}

