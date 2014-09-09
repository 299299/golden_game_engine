#include "TestGameState.h"
//==================================================
#include "Engine.h"
#include "MathDefs.h"
#include "Memory.h"
#include "Log.h"
#include "Win32Context.h"
#include "Resource.h"
//==================================================
//COMPONENTS
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
#include "Camera.h"
#include "AnimRig.h"
#include "ShadingEnviroment.h"
#include "PhysicsInstance.h"
//==================================================
#include "Component.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Graphics.h"
#include "Model.h"
#include "Material.h"
#include "DebugDraw.h"
#include "Scene.h"
#include "ShadingEnviroment.h"
#include "Light.h"
#include "Level.h"
#include <imgui/imgui.h>
#include "InputController.h"

static InputController              g_inputController;
static EntityInstance*              g_player = 0;
static int                          g_testRaycast = -1;

#define  LEVEL_PACKAGE  ("data/world0.package")
#define  TEST_LEVEL     ("world0/Level_Test")

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
            if(curMode >= sizeof(debugMode)/sizeof(debugMode[0])) curMode = 0;
        }
        break;
    case VK_F2: g_engine.setUpdate(!g_engine.isUpdating()); break;
    case VK_F3: g_physicsWorld.m_update = !g_physicsWorld.m_update; break;
    case VK_F4: g_entityMgr.setBucketUpdate(kProp, !g_entityMgr.isBucketUpdate(kProp));
    default:
        break;
    }
}

TestGameState::TestGameState()
{
}

TestGameState::~TestGameState()
{

}

void TestGameState::onFirstEnter(GameState* pPrevState)
{
    extern DebugFPSCamera  g_fpsCamera;
    vec3Make(g_fpsCamera.m_eye, 0, 10, -10);
    g_fpsCamera.sync();

    Win32InputCallback cb = 
    {
        0, gameKeyCallback, 0, 0
    };
    g_win32Context.registerCallback(cb);
    m_shading = FIND_RESOURCE(ShadingEnviroment, StringId("core/common/default"));
    g_resourceMgr.loadPackage(LEVEL_PACKAGE);
}

void TestGameState::preStep(float timeStep)
{
    extern DebugFPSCamera  g_fpsCamera;
    g_fpsCamera.update(timeStep);
    float from[3] = {0, 10, 0};
    float to[3] = {0, -2, 0};
    g_testRaycast = g_physicsWorld.addRaycastJob(from, to);

    __super::preStep(timeStep);
}


void TestGameState::postStep(float timeStep)
{
    __super::postStep(timeStep);
    debug_update_vdb_camera();
    g_debugDrawMgr.addAxis(hkQsTransform::getIdentity(), 10.0f);
    float pos3d[] = {0, 5.0f, -10.0f};
    g_debugDrawMgr.add3DText("what the fuck ?", pos3d, RGBA(0,255,255,255));
    g_sceneMgr.draw_debug();
    //g_debugDrawMgr.addGrid(20, 2.5f, RGBA(125,125,125,255), false);

    int status = g_resourceMgr.getPackageStatus(StringId(LEVEL_PACKAGE));
    if(status == kResourceOffline)
    {
        g_resourceMgr.flushPackage(StringId(LEVEL_PACKAGE), 2);
    }
    else if(status == kResourceOnline)
    {
        Level* level = FIND_RESOURCE(Level, StringId(TEST_LEVEL));
        static bool bCreated = false;
        if(level && !bCreated)
        {
            bCreated = true;
            level->load(-1);
            level->flush();
        }
    }
}

void TestGameState::render()
{
#if 1
    const float fadeInTime = 5.0f;
    int width = g_win32Context.m_width;
    int height = g_win32Context.m_height;
    if(m_timeInState <= fadeInTime)
    {
        float p = (fadeInTime - m_timeInState)/fadeInTime;
        imguiDrawRect(0, 0, (float)width, (float)height, imguiRGBA(0, 0, 0, 255 * p));
    }
#endif
	__super::render();
}