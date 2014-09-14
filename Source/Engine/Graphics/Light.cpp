#include "Light.h"
#include "Resource.h"
#include "Log.h"
#include "DataDef.h"
#include "Graphics.h"
#include "MathDefs.h"
#include "Memory.h"
#include <bgfx/bgfx.h>


LightManager g_lightMgr;

void LightManager::draw()
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
}

void LightManager::update( float dt )
{
    m_numLightsToDraw = 0;
    uint32_t numLights = id_array::size(m_components);
    m_drawLights = FRAME_ALLOC(LightInstance*, numLights);
    const LightInstance* lights = id_array::begin(m_components);
    for (uint32_t i=0; i<numLights; ++i)
    {
        const LightInstance& l = lights[i];
        if(l.m_flag & kNodeInvisible) continue;
        m_drawLights[m_numLightsToDraw++] = &l;
    }
}

void LightManager::initComponent( LightInstance* inst, const void* resource )
{
    const LightResource* lightResource = (const LightResource*)resource;
    inst->m_resource = lightResource;
    memcpy(inst->m_color, lightResource->m_color, sizeof(inst->m_color));
    memcpy(inst->m_vec, lightResource->m_dir, sizeof(inst->m_vec));
    ADD_BITS(inst->m_flag, kNodeTransformDirty);
}

void LightManager::transformComponent( ComponentId id, const hkQsTransform& t )
{
    if(!id_array::has(m_components, id)) return;
    LightInstance& inst = id_array::get(m_components, id);
    if(inst.m_resource->m_type == kLightDirectional) return;
    transform_vec3(inst.m_vec, t.m_translation);
}

void LightManager::enableComponent( ComponentId id, bool bEnable )
{
    if(!id_array::has(m_components, id)) return;
    LightInstance& inst = id_array::get(m_components, id);
    if(bEnable) REMOVE_BITS(inst.m_flag, kNodeInvisible);
    else ADD_BITS(inst.m_flag, kNodeInvisible);
}


