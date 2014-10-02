#include "Graphics.h"
#include "Material.h"
#include "DebugDraw.h"
#include "ShadingEnviroment.h"
#include "Gui.h"
#include "AnimFSM.h"
#include "Light.h"
#include "Resource.h"
#include <imgui/imgui.h>
#include <bx/bx.h>
#include <gamemonkey/gmThread.h>

void create_material_debug_gui(Material* mat, const char* name)
{
    imguiLabel("material: %s", name);
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

void create_light_debug_gui(LightResource* light, const char* name)
{
    imguiLabel("light: %s", name);
    static bool bEnable = false;
    imguiColorWheel("color:", light->m_color, bEnable);
    imguiSlider("falloff", light->m_fallOff, 0.0f, 1.0f, 0.1f);
    imguiSlider("intensity", light->m_intensity, 0.0f, 1.0f, 0.1f);
    imguiSlider("coneAngle", light->m_coneAngle, 0.0f, 1.0f, 0.1f);
    imguiSlider("attenScale", light->m_attenScale, 0.0f, 1.0f, 0.1f);
    imguiSeparator();
}

void create_postprocess_debug_gui()
{
    extern PostProcess  g_postProcess;
    static int32_t scroll = 0;
    imguiBeginScrollArea("post-process", 0, 50, 300, 800, &scroll);

    int width = 256;
    ImguiAlign::Enum align = ImguiAlign::CenterIndented;
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

void create_shading_enviroment_gui(ShadingEnviroment* shading_env, const char* name)
{
    imguiLabel("ShadingEnviroment: %s", name);

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
}

//--------------------------------------------------------------------------
// SCRIPT FUNCTIONS
static int GM_CDECL script_material_debug_gui(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 3);
    GM_CHECK_STRING_PARAM(mat_name, 4);
    Material* m = FIND_RESOURCE(Material, StringId(mat_name));
    if(!m) return GM_OK;
    static int scroll = 0;
    imguiBeginScrollArea("material", (int)x, (int)y, (int)w, (int)h, &scroll);
    create_material_debug_gui(m, mat_name);
    imguiEndScrollArea();
    return GM_OK;
}

static int GM_CDECL script_light_debug_gui(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 3);
    GM_CHECK_STRING_PARAM(light_name, 4);
    LightResource* lt = FIND_RESOURCE(LightResource, StringId(light_name));
    if(!lt) return GM_OK;
    static int scroll = 0;
    imguiBeginScrollArea("light", (int)x, (int)y, (int)w, (int)h, &scroll);
    create_light_debug_gui(lt, light_name);
    imguiEndScrollArea();
    return GM_OK;
}

static int GM_CDECL script_shading_enviroment_debug_gui(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 3);
    GM_CHECK_STRING_PARAM(shading_name, 4);
    ShadingEnviroment* shading_env = FIND_RESOURCE(ShadingEnviroment, StringId(shading_name));
    if(!shading_env) return GM_OK;
    static int scroll = 0;
    imguiBeginScrollArea("shading_enviroment", (int)x, (int)y, (int)w, (int)h, &scroll);
    create_shading_enviroment_gui(shading_env, shading_name);
    imguiEndScrollArea();
    return GM_OK;
}

static int GM_CDECL script_post_process_debug_gui(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 3);
    static int scroll = 0;
    imguiBeginScrollArea("post_process", (int)x, (int)y, (int)w, (int)h, &scroll);
    create_postprocess_debug_gui();
    imguiEndScrollArea();
    return GM_OK;
}


void register_debug_gui_api(gmMachine* machine)
{
    static gmFunctionEntry s_script_binding[] =  
    {
        {"debug_material", script_material_debug_gui },
        {"debug_light", script_light_debug_gui },
        {"debug_shading_enviroment", script_shading_enviroment_debug_gui },
        {"debug_post_process", script_post_process_debug_gui },
    };
    machine->RegisterLibrary(s_script_binding, BX_COUNTOF(s_script_binding), "debug");
}