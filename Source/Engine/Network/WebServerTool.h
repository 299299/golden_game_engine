#pragma once
#include "gamedevwebtools.h"
#include "Prerequisites.h"

struct WebServerTool : public gamedevwebtools::Service
{
    void start(uint32_t netPort);
    void frameStarted(float dt);
    void onLogMessage(int logLevel, const char* logMsg);

    virtual void *onMalloc(size_t size);
    virtual void onFree(void *ptr);

    virtual void onError(const char *errorString);
    virtual void onNewClient();

    void onRequestQuit();
    void onRequestActive();
    void onRequestStep();
    void onKeyDown(const gamedevwebtools::Message &message);
    void onKeyUp(const gamedevwebtools::Message &message);

    float                   m_updateTimer;
    float                   m_elapsedTime;
};


extern WebServerTool* g_webServerTool;
void initWebServerTool(uint32_t netPort);
void quitWebServerTool();
