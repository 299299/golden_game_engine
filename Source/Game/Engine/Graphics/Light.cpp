#include "Light.h"
#include "Resource.h"
#include "Log.h"
#include "DataDef.h"
#include "Graphics.h"
#include "ShadingEnviroment.h"
#include "MathDefs.h"
#include "MemorySystem.h"
#include "IdArray.h"
#include "Profiler.h"

LightWorld g_lightWorld;
static IdArray<Light>  m_lights;

void LightWorld::init(int max_light)
{
    reset();
    bx::mtxIdentity(m_shadowView);
    bx::mtxIdentity(m_shadowProj);
    m_lights.init(max_light, g_memoryMgr.get_allocator(kMemoryCategoryCommon));
}

void LightWorld::shutdown()
{
    m_lights.destroy();
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

    int numLights = m_lights.size();
    m_drawLights = FRAME_ALLOC(Light*, numLights);
    Light* lights = m_lights.begin();
    for (int i=0; i<numLights; ++i)
    {
        Light& l = lights[i];
        if(l.m_flag & kNodeInvisible) continue;
        if(l.m_hasShadow && !m_shadowLight) m_shadowLight = &l;
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
    Light** lights = (Light**)m_drawLights;
    for (uint32_t i = 0; i < num; ++i)
    {
        const Light* light = lights[i];
        Vec4& info = s_lightInfo[i];
        Vec3& color = s_lightColor[i];
        Vec3& vec = s_lightVec[i];
        s_lightType[i] = light->m_type;
        bx::vec3Move(color.m_vec, light->m_color);
        if(s_lightType[i] == kLightDirectional) bx::vec3Move(vec.m_vec, light->m_dir);
        else vec3_make(vec.m_vec, light->m_transform[12], light->m_transform[13], light->m_transform[14]);
        info.m_vec[0] = light->m_fallOff;
        info.m_vec[1] = light->m_intensity;
        info.m_vec[2] = light->m_coneAngle;
        info.m_vec[3] = light->m_attenScale;
    }

    extern UniformPerLight      g_uniformLights;
    bgfx::setUniform(g_uniformLights.m_color, s_lightColor, num);
    bgfx::setUniform(g_uniformLights.m_vec, s_lightVec, num);
    bgfx::setUniform(g_uniformLights.m_info, s_lightInfo, num);
    bgfx::setUniform(g_uniformLights.m_type, s_lightType, num);

    if(!m_shadowLight)
        return;

    extern ShadowMap g_shadowMap;
    bgfx::setViewRect(kShadowViewId, 0, 0, g_shadowMap.m_shadowMapSize, g_shadowMap.m_shadowMapSize);
    bgfx::setViewFrameBuffer(kShadowViewId, g_shadowMap.m_shadowMapFB->m_handle);
    bgfx::setViewTransform(kShadowViewId, m_shadowView, m_shadowProj);
    bgfx::setUniform(g_shadowMap.m_paramUniform, env->m_shadow_params);

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

    switch(m_shadowLight->m_type)
    {
    case kLightDirectional:
        {
            bx::vec3Mul(shadowEye, m_shadowLight->m_dir, -1);
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
    m_shadowFrustum.build_view_frustum(m_shadowView, m_shadowProj);
}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
Id create_light(const void* res, ActorId32 actorId)
{
    Light* inst;
    Id lightId = m_lights.create(&inst);
    memcpy(inst, res, sizeof(Light));
    return lightId;
}

void destroy_light(Id id)
{
    if(!m_lights.has(id)) return;
    m_lights.destroy(id);
}


void*  get_light(Id id)
{
    if(!m_lights.has(id)) return 0;
    return m_lights.get(id);
}

int num_all_light()
{
    return m_lights.size();
}

void* get_all_light()
{
    return m_lights.begin();
}

void transform_light(Id id, const hkQsTransform& t)
{
    if(!m_lights.has(id))
        return;
    Light* light = m_lights.get(id);
#ifdef HAVOK_COMPILE
    t.get4x4ColumnMajor(light->m_transform);
    ADD_BITS(light->m_flag, kNodeTransformDirty);
#endif
}

#include "DebugDraw.h"
void debug_draw_lights()
{
    PROFILE(debug_draw_lights);
    int num = m_lights.size();
    Light* lights = m_lights.begin();
    bool bShadow = false;

    for (int i=0; i<num; ++i)
    {
        const Light& lt = lights[i];
        switch(lt.m_type)
        {
        case kLightDirectional:
            {
                float start[3] = {0, 10, 0};
                float end[3];
                bx::vec3Mul(end, lt.m_dir, 10.0f);
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
                        g_debugDrawMgr.add_line(tmp1, tmp2, RGBA(252,177,67,255), true);
                    }
                }

                if(lt.m_hasShadow) bShadow = true;
            }
            break;
        case kLightPoint:
        case kLightSpot:
            {
                const float* m = lt.m_transform;
                float pos[3] = {m[12], m[13], m[14]};
                g_debugDrawMgr.add_cross(pos, 1.0f, RGBA(255,0,0,255), true);
            }
            break;
        }
    }

    if(bShadow) g_debugDrawMgr.add_frustum(g_lightWorld.m_shadowFrustum, RGBA(0,106,106,181), true);
}
//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
