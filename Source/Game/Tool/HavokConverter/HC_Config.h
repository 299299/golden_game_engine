#pragma once
#include "ToolUtils.h"

#define     COMMON_MAT_NAME     ("lambert1")
#define     PROXY_NAME          ("Proxy_")
#define     LEVEL_NAME          ("Level")
#define     ENGINE_ATTRIBUTES   ("engine_attributes")
//#define   HC_DUMP_PROFILE

#ifdef HC_DUMP_PROFILE
#define HC_PROFILE(name)      PROFILE(name)
#else
#define HC_PROFILE(name)       
#endif

struct HC_Config
{
    HC_Config()
    :m_numThreads(0)
    ,m_packNormal(false)
    ,m_packUV(false)
    ,m_slient(false)
    ,m_verbose(false)
    {
    }

    ToolError                   m_error;
    std::string                 m_inputDir;
    int                         m_numThreads;
    bool                        m_packNormal;
    bool                        m_packUV;
    bool                        m_slient;
    bool                        m_verbose;
};

class hkpPhysicsData;
class hkaAnimationContainer;
class hkxScene;
class hkRootLevelContainer;
class hkLoader;

struct Actor_Config
{
    Actor_Config()
        :m_exportClass("level_geometry")
        ,m_exportMode("model")
        ,m_loader(0)
        ,m_rlc(0)
        ,m_animation(0)
        ,m_physics(0)
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

    hkLoader*                   m_loader;
    hkRootLevelContainer*       m_rlc;
    hkxScene*                   m_scene;
    hkaAnimationContainer*      m_animation;
    hkpPhysicsData*             m_physics;
};


extern HC_Config* g_hc_config;


#ifndef HAVOK_COMPILE
#define HK_DECLARE_CLASS_ALLOCATOR(...)
#define HK_MEMORY_CLASS_USER
class hkReferencedObject
{
public:
    virtual ~hkReferencedObject() {};
    virtual void removeReference() {};
};

#endif