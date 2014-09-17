#include "RemoteViewerState.h"
//==================================================
#include "Engine.h"
#include "MathDefs.h"
#include "MemorySystem.h"
#include "Log.h"
#include "Win32Context.h"
#include "Resource.h"
#include "Camera.h"
#include "ShadingEnviroment.h"
#include "EntityManager.h"
#include "Graphics.h"
#include "DebugDraw.h"
#include "Scene.h"
#include "WebServerTool.h"
#include "Level.h"
#include "Entity.h"
#include "PhysicsInstance.h"
#include <bx/bx.h>
#include <imgui/imgui.h>

extern char g_entityName[];
extern char g_levelName[];
extern void resource_hot_reload_init();
extern void console_command(const gamedevwebtools::Message &message);
extern void find_package_path(const char* intput, char* packagePath);

static void gameKeyCallback(uint32_t key, bool down)
{
    if(!down)
        return;
    switch(key)
    {
    case VK_ESCAPE:
        g_engine.shutdown();
        break;
    case VK_F1:
        {
            static uint32_t debugMode[] = {BGFX_DEBUG_NONE, BGFX_DEBUG_STATS, BGFX_DEBUG_TEXT, BGFX_DEBUG_WIREFRAME};
            static int curMode = 0;
            bgfx::setDebug(debugMode[curMode]);
            ++curMode; 
            if(curMode >= BX_COUNTOF(debugMode)) curMode = 0;
        }
        break;
    case VK_F2: g_engine.setUpdate(!g_engine.isUpdating()); break;
    default:
        break;
    }
}

void RemoteViewerState::init()
{
    __super::init();
    g_webServerTool->connect("remote.command", console_command);
    resource_hot_reload_init();
}

void RemoteViewerState::onFirstEnter( GameState* pPrevState )
{
    extern DebugFPSCamera  g_fpsCamera;
    vec3Make(g_fpsCamera.m_eye, 0, 10, -10);
    g_fpsCamera.sync();
    m_shading = FIND_RESOURCE(ShadingEnviroment, StringId("core/common/default"));

    Win32InputCallback cb = 
    {
        0, gameKeyCallback, 0, 0
    };
    g_win32Context.registerCallback(cb);

    if(strlen(g_entityName) > 0)
    {
        LOGI("load preview actor %s", g_entityName);
        char packagePath[256];
        find_package_path(g_entityName, packagePath);
        g_resourceMgr.loadPackageAndWait(packagePath);
        g_entityMgr.addInstance(StringId(g_entityName), hkQsTransform::getIdentity());
    }
    else if(strlen(g_levelName) > 0)
    {
        char packagePath[256];
        find_package_path(g_levelName, packagePath);
        g_resourceMgr.loadPackageAndWait(packagePath);
        Level* level = FIND_RESOURCE(Level, StringId(g_levelName));
        if(level) 
        {
            level->load(-1);
            level->flush();
        }
        else 
        {
            LOGE("can not find level %s", g_levelName);
        }
    }
}

void RemoteViewerState::frameStart(float timeStep)
{
    __super::frameStart(timeStep);
    g_webServerTool->frameStarted(timeStep);
}

void RemoteViewerState::preStep( float timeStep )
{
    extern DebugFPSCamera  g_fpsCamera;
    g_fpsCamera.update(timeStep);
    __super::preStep(timeStep);
}

void RemoteViewerState::postStep( float timeStep )
{
    g_entityMgr.postStep(timeStep);
    Graphics::update(timeStep);
    dbgPrintfEngineStatus(false);
    if(strlen(g_entityName) > 0) DBG_TEX_PRINTF(0x2f, "actor name = %s", g_entityName);
    else DBG_TEX_PRINTF(0x2f, "level name = %s", g_levelName);
    g_debugDrawMgr.addAxis(hkQsTransform::getIdentity(), 10.0f);
    g_sceneMgr.draw_debug();
}

