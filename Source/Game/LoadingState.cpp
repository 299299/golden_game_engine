#include "LoadingState.h"
#include "Resource.h"
#include "Memory.h"
#include "Graphics.h"
#include "DebugDraw.h"
#include "Scene.h"
#include "ShadingEnviroment.h"
#include "Engine.h"
#include "Win32Context.h"
#include <imgui/imgui.h>

void LoadingState::setLoadingPackage(const char* packageName)
{
    m_packageName = packageName;
    m_loadPackageName = StringId(packageName);
}

void LoadingState::setLoadingFinishState(const StringId& stateName)
{
    m_finishStateName = stateName;
}

void LoadingState::onEnter(GameState* pPrevState)
{
    __super::onEnter(pPrevState);
    m_nextStateName = StringId::ZERO;
    g_resourceMgr.loadPackage(m_packageName);
}

void LoadingState::preStep(float timeStep)
{
    if(g_win32Context.m_keyStatus[VK_ESCAPE])
        g_engine.shutdown();

    int status = g_resourceMgr.getPackageStatus(m_loadPackageName);
    if(status == kResourceOnline)
    {
        static bool bPostInited = false;
        if(!bPostInited)
        {
            Graphics::postInit();
            bPostInited = true;
        }
        m_nextStateName = m_finishStateName;
    }
    else if(status == kResourceOffline)
    {
        g_resourceMgr.flushPackage(m_loadPackageName, 2);
    }
    __super::preStep(timeStep);
}

void LoadingState::postStep( float timeStep )
{
    __super::postStep(timeStep);
}

void LoadingState::render()
{
    int width = g_win32Context.m_width;
    int height = g_win32Context.m_height;
    imguiDrawRect(0, 0, (float)width, (float)height, imguiRGBA(0, 0, 0, m_timeInState*10));
    __super::render();
}