#include "WebServerTool.h"
#include "DataDef.h"
#include "Engine.h"
#include "MemorySystem.h"
#include "Log.h"
#include "Win32Context.h"

using namespace gamedevwebtools;
WebServerTool* g_webServerTool = 0;

#define WEB_TICK_TIME   (1.0f/2.0f)

void initWebServerTool(uint32_t netPort)
{
    g_webServerTool = new WebServerTool;
    g_webServerTool->start(netPort);
}

void quitWebServerTool()
{
    SAFE_DELETE(g_webServerTool);
}

void frame_start_websocket( float dt )
{
    if(!g_webServerTool) return;
    g_webServerTool->frame_start(dt);
}

void WebServerTool::start(uint32_t netPort)
{
    LOGI("WebServerTool-->start %d", netPort);
    m_updateTimer = 0.0f;

    Service::ApplicationInformation info;
    info.name = "GameProject Debug WebServer";
    Service::NetworkOptions netOpts;
    netOpts.maxConnectedClients = 2;
    netOpts.port = 6161;
    init(info,netOpts,1);
    
    connect("application.service.quit", *this ,&WebServerTool::on_request_quit);
    connect("application.service.activate",*this ,&WebServerTool::on_request_active);
    connect("application.service.step",*this ,&WebServerTool::on_request_step);
    connect("input.keydown",*this,&WebServerTool::on_request_keydown);
    connect("input.keyup",*this,&WebServerTool::on_request_keyup);
}


void WebServerTool::frame_start(float dt)
{
    frameStart(dt);

    extern uint32_t g_frameId;
    extern float  g_totalSeconds;

    m_updateTimer += dt;
    if(m_updateTimer >= WEB_TICK_TIME)
    {
        send(Message("monitoring.frame",
            Message::Field("id",g_frameId),
            Message::Field("dt",dt),
            Message::Field("t",g_totalSeconds)));
        Message staticMemMsg("monitoring.memory",
            Message::Field("name","common-alloc"),
            Message::Field("t",g_frameId),
            Message::Field("size", g_memoryMgr.allocated_size(kMemoryCategoryCommon)));
        send(staticMemMsg);
        Message frameMemMsg("monitoring.memory",
            Message::Field("name","frame-alloc"),
            Message::Field("t",g_frameId),
            Message::Field("size", g_memoryMgr.allocated_size(kMemoryCategoryFrame)));
        send(frameMemMsg);
        m_updateTimer -= WEB_TICK_TIME;
    }
    update();
}

void WebServerTool::on_log_message(int logLevel, const char* logMsg)
{
    send(Message("logging.msg", 
         Message::Field("lvl",logLevel),
         Message::Field("msg",logMsg)));
}

void WebServerTool::on_request_quit()
{
    g_engine.shutdown();
}

void WebServerTool::on_request_active()
{
    g_engine.set_update(!g_engine.updating());
}

void WebServerTool::on_request_step()
{
    g_engine.frame(1.0f/60.0f);
}

void WebServerTool::onError(const char *errorString)
{
    LOGE("WebServerTool error %s.", errorString);
    //g_engine.shutdown();
}

void WebServerTool::onNewClient()
{
    LOGD("WebServerTool NewClient.");
}

void WebServerTool::on_request_keydown(const Message &message)
{
    int keyCode = message.fields()[0].asInteger();
    LOGD("OnKeyDown = %d", keyCode);
    g_win32Context.m_keyStatus[keyCode] = true;
}

void WebServerTool::on_request_keyup(const Message &message)
{
    int keyCode = message.fields()[0].asInteger();
    LOGD("OnKeyDown = %d", keyCode);
    g_win32Context.m_keyStatus[keyCode] = false;
}
