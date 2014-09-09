#include "Scene.h"
#include "Model.h"
#include "Light.h"
#include "MemoryPool.h"
#include "Memory.h"
#include "Log.h"
#include "MathDefs.h"
#include "DataDef.h"
#include "Graphics.h"
#include "Shader.h"
#include "DebugDraw.h"
#include "Profiler.h"
#include "ShaderInc.h"
#include "Resource.h"
#include "Component.h"
#include "ShadingEnviroment.h"

SceneManager g_sceneMgr;
float shadowLightView[16];
float shadowLightProj[16];

static DynamicObjectComponentFactory<ModelInstance>       g_modelList(ModelResource::getName(), 2000);
static DynamicObjectComponentFactory<LightInstance>       g_lightList(LightResource::getName(), 30);
static Frustum g_shadowFrustum;

static Vec4 s_lightInfo[BGFX_CONFIG_MAX_LIGHTS];
static Vec3 s_lightColor[BGFX_CONFIG_MAX_LIGHTS];
static Vec3 s_lightVec[BGFX_CONFIG_MAX_LIGHTS];
static int  s_lightType[BGFX_CONFIG_MAX_LIGHTS];

void SceneManager::init()
{
    g_componentMgr.registerFactory(&g_modelList);
    g_componentMgr.registerFactory(&g_lightList);
    bx::mtxIdentity(shadowLightView);
    bx::mtxIdentity(shadowLightProj);
}

void SceneManager::quit()
{
    
}

void SceneManager::cullRenderers(const Frustum& frust)
{
    m_lightList.m_renderables  = FRAME_ALLOC(void*, g_lightList.m_objects.getSize());
    m_lightList.m_numVisibles = 0;
    m_shadowLight = 0;

    m_modelList.m_renderables  = FRAME_ALLOC(void*, g_modelList.m_objects.getSize());
    m_modelList.m_numVisibles = 0;

    DynamicObjectArray<LightInstance>& lightList = g_lightList.m_objects;
    uint32_t numLights = lightList.getSize();
    for(uint32_t i=0; i<numLights; ++i)
    {
        LightInstance& inst = lightList[i];
        if(inst.m_flag & kNodeInvisible)
            continue;
        if(inst.m_resource->m_hasShadow)
            m_shadowLight = &inst;
        m_lightList.m_renderables[m_lightList.m_numVisibles++] = &lightList[i];
    }
    
    DynamicObjectArray<ModelInstance>& modelList = g_modelList.m_objects;
    uint32_t numModels = modelList.getSize();
    for(uint32_t i=0; i<numModels; ++i)
    {
        ModelInstance& inst = modelList[i];
        if(inst.m_flag & kNodeInvisible)
            continue;
        bool bVisible = !frust.cullBox(inst.m_aabb.m_min, inst.m_aabb.m_max);
        inst.m_visibleThisFrame = bVisible;
        if(!bVisible) continue;
        m_modelList.m_renderables[m_modelList.m_numVisibles++] = &modelList[i];
    }
}

void SceneManager::cullShadows(float shadowArea, float shadowSize, const float* camPos)
{
    m_modelShadowList.m_numVisibles = 0;
    if(!m_shadowLight) return;

    DynamicObjectArray<ModelInstance>& modelList = g_modelList.m_objects;
    uint32_t numModels = modelList.getSize();
    m_modelShadowList.m_renderables  = FRAME_ALLOC(void*, numModels);

    float shadowEye[3] = {0,0,0};
    float shadowAt[3] = {0,0,0};

    switch(m_shadowLight->m_resource->m_type)
    {
    case kLightDirectional:
        {
            bx::vec3Mul(shadowEye, m_shadowLight->m_vec, -1);
            shadowEye[0] += camPos[0];
            shadowEye[2] += camPos[2];
            shadowAt[0] = camPos[0];
            shadowAt[2] = camPos[2];
        }
        break;
    case kLightSpot:
        break;
    case kLightPoint:
        break;
    }

    bx::mtxLookAt(shadowLightView, shadowEye, shadowAt);
    bx::mtxOrtho(shadowLightProj, -shadowArea, shadowArea, -shadowArea, shadowArea, -shadowSize, shadowSize);
    g_shadowFrustum.buildViewFrustum(shadowLightView, shadowLightProj);
    
    for(uint32_t i=0; i<numModels; ++i)
    {
        ModelInstance& inst = modelList[i];
        bool bSkip = (inst.m_flag & kNodeInvisible) || (inst.m_flag & kNodeNoShadow);
        if(bSkip) continue;
        bool bVisible = !g_shadowFrustum.cullBox(inst.m_aabb.m_min, inst.m_aabb.m_max);
        if(!bVisible) continue;
        m_modelShadowList.m_renderables[m_modelShadowList.m_numVisibles++] = &modelList[i];
    }
}


void SceneManager::update(float dt)
{
    DynamicObjectArray<LightInstance>& lightList = g_lightList.m_objects;
    DynamicObjectArray<ModelInstance>& modelList = g_modelList.m_objects;
    
    for(uint32_t i=0; i<lightList.getSize(); ++i)
    {
        lightList[i].update();
    }

    for(uint32_t i=0; i<modelList.getSize(); ++i)
    {
        modelList[i].update();
    }
}

void SceneManager::submitLights()
{
    memset(s_lightInfo, 0x00, sizeof(s_lightInfo));
    memset(s_lightColor, 0x00, sizeof(s_lightColor));
    memset(s_lightVec, 0x00, sizeof(s_lightVec));
    memset(s_lightType, 0x00, sizeof(s_lightType));

    //submit light information first.
    uint32_t num = m_lightList.m_numVisibles > BGFX_CONFIG_MAX_LIGHTS ? BGFX_CONFIG_MAX_LIGHTS : m_lightList.m_numVisibles;
    LightInstance** lights = (LightInstance**)m_lightList.m_renderables;
    for (uint32_t i = 0; i < num; ++i)
    {
        const LightInstance* light = lights[i];
        const LightResource* res = light->m_resource;
        Vec4& info = s_lightInfo[i];
        Vec3& color = s_lightColor[i];
        Vec3& vec = s_lightVec[i];
        s_lightType[i] = res->m_type;
        bx::vec3Move(color.m_vec, light->m_color);
        bx::vec3Move(vec.m_vec, light->m_vec);
        info.m_vec[0] = res->m_fallOff;
        info.m_vec[1] = res->m_intensity;
        info.m_vec[2] = res->m_coneAngle;
        info.m_vec[3] = res->m_attenScale;
    }

    extern UniformPerLight      g_uniformLights;
    bgfx::setUniform(g_uniformLights.m_color, s_lightColor, num);
    bgfx::setUniform(g_uniformLights.m_vec, s_lightVec, num);
    bgfx::setUniform(g_uniformLights.m_info, s_lightInfo, num);
    bgfx::setUniform(g_uniformLights.m_type, s_lightType, num);
}

void SceneManager::submit()
{
    PROFILE(SceneManager_Draw);
    submitLights();
    submitModels();
    submitShadow();
}

void SceneManager::submitModels()
{
    ModelInstance** models = (ModelInstance**)m_modelList.m_renderables;
    for(uint32_t i=0; i<m_modelList.m_numVisibles; ++i)
    {
        ModelInstance* model = models[i];
        model->submit();
    }
}

void SceneManager::submitShadow()
{
    if(!m_shadowLight) return;
    ModelInstance** models = (ModelInstance**)m_modelShadowList.m_renderables;
    for(uint32_t i=0; i<m_modelShadowList.m_numVisibles; ++i)
    {
        ModelInstance* model = models[i];
        model->submitShadow();
    }
}

//====================================================
//  debug draw...
//====================================================
void SceneManager::draw_debug()
{
    LightInstance** lights = (LightInstance**)m_lightList.m_renderables;
    bool bShadow = false;

    for(uint32_t i=0; i<m_lightList.m_numVisibles; ++i)
    {
        LightInstance* light = lights[i];
        const LightResource* res = light->m_resource;
        switch(res->m_type)
        {
        case kLightPoint:
            g_debugDrawMgr.addSphere(light->m_vec, 1.0f, RGBA(255,0,0,255), true);
            break;
        case kLightDirectional:
            {
                float start[3] = {0, 10, 0};
                float end[3];
                bx::vec3Mul(end, light->m_vec, 10.0f);
                float UP[3] = {0, 1, 0};
                float RIGHT[3] = {1, 0, 0};
                float offset[3];
                float tmp1[3], tmp2[3];

                for (int i = -1; i < 2; ++i)
                {
                    for (int j = -1; j < 2; ++j)
                    {
                        bx::vec3Mul(tmp1, UP, 5.0f*i);
                        bx::vec3Mul(tmp2, RIGHT, 5.0f*j);
                        bx::vec3Add(offset, tmp1, tmp2);
                        bx::vec3Add(tmp1, start, offset);
                        bx::vec3Add(tmp2, end, offset);
                        g_debugDrawMgr.addLine(tmp1, tmp2, RGBA(255,0,0,255), true);
                    }
                }

                if(res->m_hasShadow) bShadow = true;
            }
            break;
        case kLightSpot:
            g_debugDrawMgr.addSphere(light->m_vec, 1.0f, RGBA(255,0,0,255), true); //TODO -->
            break;
        }
    }

    if(bShadow) g_debugDrawMgr.addFrustum(g_shadowFrustum, RGBA(0,12,255,255), true);

    ModelInstance** models = (ModelInstance**)m_modelList.m_renderables;
    for(uint32_t i=0; i<m_modelList.m_numVisibles; ++i)
    {
        const ModelInstance* model = models[i];
        const Aabb& aabb = model->m_aabb;
        g_debugDrawMgr.addAabb(aabb.m_min, aabb.m_max, RGBA(0,255,0,255), true); 
    }
}

void SceneManager::preCulling( const Frustum& frust, const float* camPos, float shadowArea, float shadowSize )
{
    cullRenderers(frust);
    cullShadows(shadowArea, shadowSize, camPos);
}

