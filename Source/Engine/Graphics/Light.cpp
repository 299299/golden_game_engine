#include "Light.h"
#include "Resource.h"
#include "Log.h"
#include "DataDef.h"
#include "Graphics.h"
#include "ShadingEnviroment.h"
#include "MathDefs.h"
#include "MemorySystem.h"
#include "id_array.h"
#include "config.h"
#include <bgfx/bgfx.h>

LightWorld g_lightWorld;
static IdArray<MAX_LIGHTS, LightInstance>  m_lights;

void LightWorld::init()
{
    reset();
    bx::mtxIdentity(m_shadowView);
    bx::mtxIdentity(m_shadowProj);
}


void LightWorld::reset()
{
    m_numLightsToDraw = 0;
    m_drawLights = 0;
    m_shadowLight = 0;
}

void LightWorld::update( float dt )
{
    reset();

    uint32_t numLights = id_array::size(m_lights);
    m_drawLights = FRAME_ALLOC(LightInstance*, numLights);
    LightInstance* lights = id_array::begin(m_lights);
    for (uint32_t i=0; i<numLights; ++i)
    {
        LightInstance& l = lights[i];
        if(l.m_flag & kNodeInvisible) continue;
        if(l.m_resource->m_hasShadow && !m_shadowLight) m_shadowLight = &l;
        m_drawLights[m_numLightsToDraw++] = &l;
    }
}

void LightWorld::submit_lights(ShadingEnviroment* env)
{
    Vec4 s_lightInfo[BGFX_CONFIG_MAX_LIGHTS];
    Vec3 s_lightColor[BGFX_CONFIG_MAX_LIGHTS];
    Vec3 s_lightVec[BGFX_CONFIG_MAX_LIGHTS];
    int  s_lightType[BGFX_CONFIG_MAX_LIGHTS];

    memset(s_lightInfo, 0x00, sizeof(s_lightInfo));
    memset(s_lightColor, 0x00, sizeof(s_lightColor));
    memset(s_lightVec, 0x00, sizeof(s_lightVec));
    memset(s_lightType, 0x00, sizeof(s_lightType));

    //submit light information first.
    uint32_t num = m_numLightsToDraw > BGFX_CONFIG_MAX_LIGHTS ? BGFX_CONFIG_MAX_LIGHTS : m_numLightsToDraw;
    LightInstance** lights = (LightInstance**)m_drawLights;
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

    if(!m_shadowLight) return;
    extern ShadowMap g_shadowMap;
    bgfx::setViewRect(kShadowViewId, 0, 0, g_shadowMap.m_shadowMapSize, g_shadowMap.m_shadowMapSize);
    bgfx::setViewFrameBuffer(kShadowViewId, g_shadowMap.m_shadowMapFB->m_handle);
    bgfx::setViewTransform(kShadowViewId, m_shadowView, m_shadowProj);
    bgfx::setUniform(g_shadowMap.m_paramUniform, env->m_shadowParams);

    const float mtxCrop[16] =
    {
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f,
    };

    float mtxTmp[16];
    float mtxShadow[16];
    bx::mtxMul(mtxTmp, m_shadowProj, mtxCrop);
    bx::mtxMul(mtxShadow, m_shadowView, mtxTmp);
    bgfx::setUniform(g_shadowMap.m_lightMtx, mtxShadow);
}

void LightWorld::update_shadow(float shadowArea, float shadowSize, const float* camPos)
{
    if(!m_shadowLight) return;

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

    bx::mtxLookAt(m_shadowView, shadowEye, shadowAt);
    bx::mtxOrtho(m_shadowProj, -shadowArea, shadowArea, -shadowArea, shadowArea, -shadowSize, shadowSize);
    m_shadowFrustum.buildViewFrustum(m_shadowView, m_shadowProj);
}

LightId LightWorld::create_light(const LightResource* lightResource)
{
    LightInstance inst;
    inst.m_resource = lightResource;
    memcpy(inst.m_color, lightResource->m_color, sizeof(inst.m_color));
    memcpy(inst.m_vec, lightResource->m_dir, sizeof(inst.m_vec));
    ADD_BITS(inst.m_flag, kNodeTransformDirty);
    return id_array::create(m_lights, inst);
}

void LightWorld::destroy_light(LightId id)
{
    if(!id_array::has(m_lights, id)) return;
    id_array::destroy(m_lights, id);
}


LightInstance*  LightWorld::get_light(LightId id)
{
    if(!id_array::has(m_lights, id)) return 0;
    return &id_array::get(m_lights, id);
}

uint32_t LightWorld::num_lights()
{
    return id_array::size(m_lights);
}

LightInstance* LightWorld::get_lights()
{
    return id_array::begin(m_lights);
}