#include "RenderViewerState.h"
//==================================================
#include "Engine.h"
#include "MathDefs.h"
#include "MemorySystem.h"
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
#include "PhysicsInstance.h"
#include "Level.h"
#include <imgui/imgui.h>

static LightInstance*               g_light = 0;
static Frustum                      g_cameraFrustum;
static int                          g_guiMode = 0;

#define  LEVEL_PACKAGE  ("data/world0.package")
#define  TEST_LEVEL     ("world0/Level_Test")

extern void getCameraRay(hkVector4& outFrom, hkVector4& outTo, hkVector4& outDir);
extern void destroyMouseSpring();
extern void createMouseSpring();
extern void moveMouseSpring();

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
    case VK_F3: memcpy(&g_cameraFrustum, &g_camera.m_frustum ,sizeof(g_cameraFrustum)); break;
    case VK_F4: ++g_guiMode; if(g_guiMode >= 2) g_guiMode = 0; break;
    default:
        break;
    }
}

void gameMouseButtonCallback(int32_t mx, int32_t my, uint32_t button, bool down)
{
    if(button == kMouseLeft)
    {
        if(down)
        {
            createMouseSpring();
        }
        else
        {
            destroyMouseSpring();
        }
    }
}

void gameMouseMoveCallback(int32_t mx, int32_t my)
{
    moveMouseSpring();   
}

void RenderViewerState::onFirstEnter(GameState* pPrevState)
{
    extern DebugFPSCamera  g_fpsCamera;
    vec3_make(g_fpsCamera.m_eye, 0, 10, -10);
    g_fpsCamera.sync();
    Win32InputCallback cb = 
    {
        0, gameKeyCallback, gameMouseButtonCallback, gameMouseMoveCallback
    };
    g_win32Context.registerCallback(cb);
    m_shading = FIND_RESOURCE(ShadingEnviroment, StringId("core/common/default"));
    g_resourceMgr.loadPackage(LEVEL_PACKAGE);
    g_entityMgr.addInstance(StringId("core/common/sun"), hkQsTransform::getIdentity());
}

void RenderViewerState::preStep(float timeStep)
{
    extern DebugFPSCamera  g_fpsCamera;
    g_fpsCamera.update(timeStep);
    __super::preStep(timeStep);
}

void RenderViewerState::postStep(float timeStep)
{
    __super::postStep(timeStep);
    debug_update_vdb_camera();
    g_debugDrawMgr.addAxis(hkQsTransform::getIdentity());

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
            level->load();
            level->update();
        }
    }
}

static void createMaterialDebugGUI(Material* mat, const char* name)
{
    char buf[128];
    sprintf_s(buf, "material: %s", name);
    imguiLabel(buf);
    static bool bEnable3 = false;
    imguiColorWheel("diffuse:", mat->m_diffuse, bEnable3);
    static bool bEnable4 = false;
    imguiColorWheel("specular:", mat->m_specular, bEnable4);
    imguiSlider("diffuse alpha", mat->m_diffuse[3], 0.0f, 1.0f, 0.1f);
    imguiSlider("specular power", mat->m_specular[3], 1.0f, 100.0f, 0.1f);

    imguiLabel("params1:");
    imguiSlider("diffuse blend normal", mat->m_params1[0], 0.0f, 1.0f, 0.01f);
    imguiSlider("normal map height", mat->m_params1[1], 0.0f, 5.0f, 0.01f);
    imguiSlider("emissive intensity", mat->m_params1[2], 0.0f, 1.0f, 0.01f);

    if(mat->m_flags & kFlagRimLighting)
    {
        imguiLabel("rim color:");
        imguiSlider("rimFresnelMin", mat->m_rimColor.m_rimFresnelMin, 0.0f, 1.0f, 0.01f);
        imguiSlider("rimFresnelMax", mat->m_rimColor.m_rimFresnelMax, 0.0f, 1.0f, 0.01f);
        imguiSlider("rimBrightness", mat->m_rimColor.m_rimBrightness, 0.0f, 10.0f, 0.01f);
    }
    if(mat->m_flags & kFlagTranslucency)
    {
        imguiLabel("translucency:");
        static bool bEnable[3] = {false, false, false};
        imguiColorWheel("SkinRampOuterColor", mat->m_translucency.m_rampOuterColor, bEnable[0]);
        imguiColorWheel("SkinRampMediumColor", mat->m_translucency.m_rampMediumColor, bEnable[1]);
        imguiColorWheel("SkinRampInnerColor", mat->m_translucency.m_rampInnerColor, bEnable[2]);
        imguiSlider("translucentDistortion", mat->m_translucency.m_info[0], 0.0f, 10.0f, 0.05f);
        imguiSlider("translucentPower", mat->m_translucency.m_info[1], 0.0f, 20.0f, 0.01f);
        imguiSlider("translucentScale", mat->m_translucency.m_info[2], 0.0f, 10.0f, 0.01f);
        imguiSlider("translucentMin", mat->m_translucency.m_info[3], 0.0f, 1.0f, 0.01f);
    }
    if(mat->m_flags & kFlagOpacity)
    {
        imguiLabel("opacity:");
        imguiSlider("Opacity", mat->m_opacityParams[0], 0.0f, 1.0f, 0.01f);
        imguiSlider("OpacityFresnelMin", mat->m_opacityParams[1], 0.0f, 1.0f, 0.01f);
        imguiSlider("OpacityFresnelMax", mat->m_opacityParams[2], 0.0f, 1.0f, 0.01f);
    }
    imguiSeparator();
}

void RenderViewerState::createPostProcessGUI()
{
    extern PostProcess          g_postProcess;
    static int32_t scroll = 0;
    imguiBeginScrollArea("post-process", 0, 50, 300, 800, &scroll);

    int width = 256;
    ImguiImageAlign::Enum align = ImguiImageAlign::CenterIndented;
    const char* fbNames[] = {"float-color-buffer", "r-depth-tex", "depth-buffer"};
    for(int i=0; i<g_postProcess.m_colorFB->m_numTextures - 1; ++i)
    {
        imguiLabel(fbNames[i]);
        imguiImage(g_postProcess.m_colorFB->m_textures[i], 0, width, width, align);
    }
    imguiLabel("hdr-bright-buf");
    imguiImage(g_postProcess.m_brightFB->m_textures[0], 0, width, width, align);
    for (int i=0; i<N_PASSES; ++i)
    {
        char name[32];
        sprintf_s(name, "blur-buf-%d", i+1);
        imguiLabel(name);
        imguiImage(g_postProcess.m_blurFB[i][1]->m_textures[0], 0, width, width, align);
    }
    imguiLabel("hdr-rgb-result");
    imguiEndScrollArea();
}

void RenderViewerState::createNormalGUI()
{
    static int scroll = 0;
    imguiBeginScrollArea("material", 0, 50, 400, 600, &scroll);

    imguiLabel("Environment:");

    ShadingEnviroment* shading_env = m_shading;
    imguiSlider("color-grading", shading_env->m_colorGradingIndex, 0, 2);

    imguiSlider("exposure", shading_env->m_bloomParams[0], 0.0f, 100.0f, 0.1f);
    imguiSlider("bloomThreshold", shading_env->m_bloomParams[1], 0.0f, 1.0f, 0.001f);
    imguiSlider("bloomWidth", shading_env->m_bloomParams[2], 0.0f, 100.0f, 0.1f);
    imguiSlider("bloomIntensity", shading_env->m_bloomParams[3], 0.0f, 100.0f, 0.1f);

    imguiSlider("focusDistance", shading_env->m_dofParams[0], 0.0f, 100.0f, 0.1f);
    imguiSlider("focusRange", shading_env->m_dofParams[1], 0.0f, 100.0f, 0.1f);
    imguiSlider("dof-blur-width", shading_env->m_dofParams[2], 0.0f, 100.0f, 0.1f);
    imguiSlider("focusFalloff", shading_env->m_dofParams[3], 0.0f, 100.0f, 0.1f);
    
    imguiSlider("defocus", shading_env->m_ppParams[2], 0.0f, 100.0f, 0.1f);
#ifdef FILM_GAIN
    imguiSlider("fimgain-noise", shading_env->m_ppParams[3], 0.0f, 100.0f, 0.1f);
#endif

    imguiSeparator();

    imguiSlider("shadow area", shading_env->m_shadowAreaSize, 1.0f, 100.0f, 1.0f);
    imguiSlider("shadow far", shading_env->m_shadowFar, 1.0f, 100.0f, 1.0f);
    imguiSlider("shadow offset", shading_env->m_shadowParams[0], 0.0f, 0.1f, 0.001f);
    imguiSlider("shadow bias", shading_env->m_shadowParams[1], 0.0f, 0.01f, 0.0001f);

    imguiSeparator();

    static bool bEnable1 = false;
    imguiColorWheel("Sky color:", shading_env->m_ambientSkyColor, bEnable1);
    static bool bEnable2 = false;
    imguiColorWheel("Ground color:", shading_env->m_ambientGroundColor, bEnable2);
    imguiSlider("fog near", shading_env->m_fogParams[0], 0.0f, 100.0f, 1.0f);
    imguiSlider("fog far", shading_env->m_fogParams[1], 0.0f, 100.0f, 1.0f);
    imguiSlider("fog density", shading_env->m_fogParams[2], 0.0f, 1.0f, 0.01f);
    imguiSlider("fog height", shading_env->m_fogParams[3], -100.0f, 100.0f, 0.1f);
    imguiSeparator();

    const char* matName = "core/actor/test_monk/Mat_Monk_Body.mat";
    static Material* mat = FIND_RESOURCE(Material, StringId(matName));
    if(mat)
    {
        createMaterialDebugGUI(mat, matName);
    }

    if(g_light)
    {
        imguiLabel("light:");
        LightResource* res = (LightResource*)g_light->m_resource;
        static bool bEnable5 = false;
        imguiColorWheel("color:", g_light->m_color, bEnable5);
        imguiSlider("falloff", res->m_fallOff, 0.0f, 1.0f, 0.1f);
        imguiSlider("intensity", res->m_intensity, 0.0f, 1.0f, 0.1f);
        imguiSlider("coneAngle", res->m_coneAngle, 0.0f, 1.0f, 0.1f);
        imguiSlider("attenScale", res->m_attenScale, 0.0f, 1.0f, 0.1f);
        imguiSeparator();
    }
    imguiEndScrollArea();
}

void RenderViewerState::render()
{
    if(g_guiMode == 0) createNormalGUI();
    else if(g_guiMode == 1) createPostProcessGUI();
	__super::render();
}
