#pragma once
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "SharedInc.h"

#define     COMMON_MAT_NAME     ("lambert1")
#define     MSG_TITLE           ("HAVOK CONVERTER")
#define     PROXY_NAME          ("Proxy_")
#define     LEVEL_NAME          ("Level")
#define     HAVOK_ERROR         ("havok_convert_error.txt")
#define     ENGINE_ATTRIBUTES   ("engine_attributes")

enum HCExitCode
{
    kExitHavokLoadError = 1,
    kExitErrorArg       = 2,
    kExitOutError       = 3,
};

struct HAVOK_Config
{
    HAVOK_Config()
    :m_numThreads(0)
    ,m_exitCode(0)
    ,m_packNormal(false)
    ,m_packUV(false)
    ,m_slient(false)
    ,m_batchMode(false)
	,m_outputDir("actor/")
    {
    }
    
    std::string                 m_inputDir;
	std::string					m_outputDir;
    int                         m_numThreads;
    int                         m_exitCode;
    bool                        m_packNormal;
    bool                        m_packUV;
    bool                        m_slient;
    bool                        m_batchMode;
};

extern HAVOK_Config             g_config;

struct Actor_Config
{
    Actor_Config()
        :m_loader(0)
        ,m_exportClass("level_geometry")
        ,m_exportMode("model")
        ,m_rlc(0)
        ,m_animation(0)
        ,m_physics(0)
        ,m_time(0)
    {
    }

    std::string                 m_workspaceFolder; 
    std::string                 m_assetFolder;
    std::string                 m_exportFolder;
    std::string                 m_exportName;
    std::string                 m_exportClass;
    std::string                 m_rootPath;
    std::string                 m_assetPath;
    std::string                 m_exportMode;
    std::string                 m_input;
    std::string                 m_output;
    uint64_t                    m_time;

    hkLoader*                   m_loader;
    hkRootLevelContainer*       m_rlc;
    hkxScene*                   m_scene;
    hkaAnimationContainer*      m_animation;
    hkpPhysicsData*             m_physics;
};
