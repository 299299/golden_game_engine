#include "ToolUtils.h"
#include "Profiler.h"
#include "CharacterConverter.h"
#include "StaticModelConverter.h"
#include "LevelConverter.h"
#include "AnimationConverter.h"
#include "linear_allocator.h"

HC_Config* g_hc_config = 0;

int havok_convert_main(int argc, bx::CommandLine* cmdline)
{
#ifdef HAVOK_COMPILE
    uint32_t timeMS = GetTickCount();
    const int numMinArgs = 3;
    if(argc < numMinArgs)
    {
        msg_box("argnum less than %d\n", numMinArgs);
        return kErrorArg;
    }

    int err = kErrorSuccess;
    LOG_INIT("HavokConverterLog.html", "Havok Converter");
    MemoryConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.m_debugMemSize = DEBUG_MEMORY_SIZE;
    cfg.m_initHavok = true;
    cfg.m_havokFrameMemSize = 0;
    cfg.m_havokMonitorMemSize = 0;
    g_memoryMgr.init(cfg);

#ifdef HC_DUMP_PROFILE
    g_profiler.init(64);
#endif

    g_hc_config = new HC_Config;
    g_hc_config->m_packNormal = cmdline->hasArg("packnormal");
    g_hc_config->m_packUV = cmdline->hasArg("packuv");
    g_hc_config->m_slient = cmdline->hasArg("slient");

    Actor_Config config;
    ActorConverter* converter = 0;
    const char* mode = cmdline->findOption('m');
    if(!mode)
    {
        g_hc_config->m_error.add_error("havok convert must specific mode args!");
        err = kErrorArg;
        goto error_exit;
    }

    const char* input = cmdline->findOption('f');
    const char* output = cmdline->findOption('o');
    if(!input)
    {
        g_hc_config->m_error.add_error("havok convert must specific f args!");
        err = kErrorArg;
        goto error_exit;
    }

    config.m_exportMode = mode;
    config.m_input = input;
    config.m_exportName = getFileName(input);
    config.m_exportFolder = "";
    config.m_rootPath = "";
    if(output)
    {
        bool has_itermediate = strstr(output, INTERMEDIATE_PATH) != 0;
        if(!has_itermediate) config.m_exportFolder = std::string(INTERMEDIATE_PATH) + output;
        string_replace(config.m_exportFolder, "\\", "/");
        add_trailing_slash(config.m_exportFolder);
        std::string path = config.m_exportFolder;
        string_replace(path, INTERMEDIATE_PATH, "");
        config.m_rootPath = path;
    }
    config.m_output = config.m_exportFolder + config.m_exportName + "." + ActorResource::get_name();

    config.m_loader = new hkLoader;
    hkRootLevelContainer* rlc = config.m_loader->load(config.m_input.c_str());
    if (!rlc)
    {
        g_hc_config->m_error.add_error("can not load input havok file %s", config.m_input.c_str());
        err = KErrorLoadHavok;
        goto error_exit;
    }

    config.m_rlc = rlc;
    createFolder(config.m_exportFolder);
    hkxEnvironment* env = LOAD_OBJECT(rlc, hkxEnvironment);
    if(env)
    {
        hkStringBuf env_str;
        env->convertToString(env_str);
        LOGI(env_str.cString());
        config.m_assetFolder = env->getVariableValue("assetFolder");
        config.m_assetPath = env->getVariableValue("assetPath");
    }

    hkaAnimationContainer* ac = LOAD_OBJECT(rlc, hkaAnimationContainer);
    hkxScene* scene = LOAD_OBJECT(rlc,hkxScene);
    hkpPhysicsData* data = LOAD_OBJECT(rlc, hkpPhysicsData);

    config.m_scene = scene;
    config.m_animation = ac;
    config.m_physics = data;

    if(config.m_exportMode == "model")
    {
        if(!scene || !scene->m_rootNode)
        {
            g_hc_config->m_error.add_error("hkx file do not has root scene node.");
            goto error_exit;
        }
        converter = new StaticModelConverter;
        converter->setClass(config.m_exportClass);
    }
    else if(config.m_exportMode == "skinning")
    {
        converter = new CharacterConverter;
        converter->setClass("character");
    }
    else if(config.m_exportMode == "level")
    {
        converter = new LevelConverter;
        config.m_output = config.m_exportFolder + config.m_exportName + "." + Level::get_name();
    }
    else if(config.m_exportMode == "animation")
    {
        converter = new AnimationConverter;
        config.m_output = config.m_exportFolder + config.m_exportName + "." + Animation::get_name();
    }
    if(!converter)
    {
        g_hc_config->m_error.add_error("havok converter export mode error.");
        err = kErrorArg;
        goto error_exit;
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

error_exit:
    SAFE_REMOVEREF(converter);
    SAFE_REMOVEREF(config.m_loader);
    if(!g_hc_config->m_slient) g_hc_config->m_error.show_error();
    SAFE_DELETE(g_hc_config);

#ifdef HC_DUMP_PROFILE
    g_profiler.dump_to_file("havokconverter_profile.txt", true, true);
    g_profiler.shutdown();
#endif

    g_memoryMgr.shutdown();

    timeMS = GetTickCount() - timeMS;
    LOGD("******************************************************");
    LOGD("******************************************************");
    LOGD("* TOTAL TIME COST = %d[MS]", timeMS);
    LOGD("******************************************************");
    LOGD("******************************************************");

    LOG_TERM();
#endif
	return kErrorSuccess;
}