#pragma once
#include "gamedevwebtools.h"
#include "Prerequisites.h"

struct WebServerTool : public gamedevwebtools::Service
{
    void start(uint32_t netPort);
    void frame_start(float dt);
    void on_log_message(int logLevel, const char* logMsg);
    virtual void onError(const char *errorString);
    virtual void onNewClient();

    void on_request_quit();
    void on_request_step();
    void on_request_keydown(const gamedevwebtools::Message &message);
    void on_request_keyup(const gamedevwebtools::Message &message);

    float                   m_updateTimer;
    float                   m_elapsedTime;
};


extern WebServerTool* g_webServerTool;
void initWebServerTool(uint32_t netPort);
void quitWebServerTool();
void frame_start_websocket(float dt);
