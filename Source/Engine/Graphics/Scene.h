#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include <bgfx.h>

struct Frustum;
struct LightInstance;
struct ModelInstance;
struct ShadingEnviroment;

struct SceneList
{
    void**           m_renderables;
    uint32_t         m_numVisibles;
};

struct SceneManager
{
    void init();
    void quit();

    void preCulling(const Frustum& frust, const float* camPos, float shadowArea, float shadowSize);
    void submit();
    void update(float dt);
    void draw_debug();

    SceneList                   m_modelList;
    SceneList                   m_modelShadowList;
    SceneList                   m_lightList;
    LightInstance*              m_shadowLight;

private:
    void cullRenderers(const Frustum& frust);
    void cullShadows(float shadowArea, float shadowSize, const float* camPos);
    void submitModels();
    void submitShadow();
    void submitLights();
};

extern SceneManager g_sceneMgr;
