#include "stdafx.h"
#include "Profiler.h"
#include "CharacterConverter.h"
#include "StaticModelConverter.h"
#include "LevelConverter.h"
#include "AnimationConverter.h"
#include "linear_allocator.h"
#include "HC_Utils.h"

HAVOK_Config g_config;

int havok_convert_main(int argc, bx::CommandLine* cmdline)
{
    DWORD timeMS = GetTickCount();
    const int numMinArgs = 3;
    if(argc < numMinArgs)
    {
        msg_box("argnum less than %d\n", numMinArgs);
        return kErrorArg;
    }

    int err = kErrorSuccess;

    LOG_INIT("HavokConverterLog.html", MSG_TITLE);
    MemoryConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.m_debugMemSize = DEBUG_MEMORY_SIZE;
    cfg.m_initHavok = true;
    cfg.m_havokFrameMemSize = 1024;
    cfg.m_havokMonitorMemSize = 0;
    g_memoryMgr.init(cfg);

    g_config.m_packNormal = cmdline.hasArg("packnormal");
    g_config.m_packUV = cmdline.hasArg("packuv");
    g_config.m_slient = cmdline.hasArg("slient"); 

    Actor_Config config;
    const char* input = cmdline.findOption('f');
    const char* output = cmdline.findOption('o');
    if(input && output) 
    {
        LOGI("havok convert %s ---> %s", input, output);
        config.m_input = input;
        config.m_exportName = getFileName(input);
        config.m_exportFolder = output;
        config.m_output = outputFile;
        std::string path = config.m_exportFolder;
        string_replace(path, INTERMEDIATE_PATH, "");
        config.m_rootPath = path;
        config.m_loader = new hkLoader;
        hkRootLevelContainer* rlc = config.m_loader->load(config.m_input.c_str());
        if (!rlc)
        {
            addError("can not load input havok file %s", config.m_input.c_str());
            err = KErrorLoadHavok;
            SAFE_REMOVEREF(config.m_loader);
            goto error_exit;
        }

        config.m_rlc = rlc;
        if(!isFolderExist(config.m_exportFolder)) createFolder(config->m_exportFolder);
        hkxEnvironment* env = LOAD_OBJECT(rlc, hkxEnvironment);
        if(env)
        {
            hkStringBuf env_str;
            env->convertToString(env_str);
            LOGI(env_str.cString());
            for(int i=0; i<env->getNumVariables(); ++i)
            {
                const char* name = env->getVariableName(i);
                if(!strcmp(name,"WORK_SPACE")) config.m_workspaceFolder = env->getVariableValue(i);
                if(!strcmp(name,"EXPORT_MODE")) config.m_exportMode = env->getVariableValue(i);
            }
            config.m_assetFolder = env->getVariableValue("assetFolder");
            config.m_assetPath = env->getVariableValue("assetPath");
        }

        hkaAnimationContainer* ac = LOAD_OBJECT(rlc, hkaAnimationContainer);
        hkxScene* scene = LOAD_OBJECT(rlc,hkxScene);
        hkpPhysicsData* data = LOAD_OBJECT(rlc, hkpPhysicsData);

        config.m_scene = scene;
        config.m_animation = ac;
        config.m_physics = data;

        ActorConverter* converter = 0;
        if(config.m_exportMode == "model")
        {
            if(!scene || !scene->m_rootNode)
            {
                SAFE_REMOVEREF(config->m_loader);
                return;
            }
            converter = new StaticModelConverter;
            converter->setClass(config->m_exportClass);
        }
        else if(config.m_exportMode == "skinning")
        {
            converter = new CharacterConverter;
            converter->setClass("character");
        }
        else if(config.m_exportMode == "level")
        {
            converter = new LevelConverter;
        }
        else if(config.m_exportMode == "animation")
        {
            converter = new AnimationConverter;
            config.m_output = config.m_exportFolder + config.m_exportName + "." + Animation::get_name();
        }
        if(!converter)
        {
            SAFE_REMOVEREF(config.m_loader);
            return;
        }

        converter->m_config = &config;
        converter->setName(config.m_exportName);
        if(config.m_exportMode == "skinning") 
        {
            converter->process(ac);
        }
        else if(config.m_exportMode == "animation") 
        {
            converter->process(ac);
        }
        else 
        {
            converter->process(scene);
        }
        converter->postProcess();
        converter->serializeToFile(config.m_output.c_str());
        SAFE_REMOVEREF(converter);
        SAFE_REMOVEREF(config.m_loader);
    }
    else 
    {
        addError("single havok convert must specific f & o args!");
        err = kErrorArg;
        goto error_exit;
    }
    g_profiler.dump_to_file("havokconverter_profile.txt", true, true);


error_exit:
    showErrorMessage(MSG_TITLE, 0, g_config.m_slient);
    g_memoryMgr.shutdown();
    

    timeMS = GetTickCount() - timeMS;
    LOGD("******************************************************");
    LOGD("******************************************************");
    LOGD("* TOTAL TIME COST = %d[MS]", timeMS);
    LOGD("******************************************************");
    LOGD("******************************************************");

    LOG_TERM();
	return kErrorSuccess;
}