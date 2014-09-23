#include "Log.h"
#include <stdarg.h>
#include <windows.h> 
#include <time.h>
#include "DataDef.h"
#include "Prerequisites.h"
#include "WebServerTool.h"
//================================================
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
//================================================

static bool                 g_logInited = false;
static char                 g_logBuffer[4096*2];
static DWORD                g_startTime = 0;
static hkCriticalSection    g_CS;
static const char*          g_loglevelTag[] =
{
    "trace",
    "debug",
    "info",
    "warn",
    "err",
    "critical",
    "fatal",
    "havok",
    "invalid"
};

Log gLogger;

Log::Log()
{
    
}

Log::~Log()
{

}

bool Log::init( const char* logFile, const char* logTitle)
{
    hkCriticalSectionLock _l(&g_CS);
    g_startTime = GetTickCount();
    // Reset log file
    m_stream.setf( std::ios::fixed );
    m_stream.precision( 3 );
    m_stream.open( logFile, std::ios::out );
    if( !m_stream ) return false;

    int width = 1440;

    m_stream << "<html>\n";
    m_stream << "<head>\n";
    m_stream << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n";
    m_stream << "<title>" << logTitle << "</title>\n";
    m_stream << "<style type=\"text/css\">\n";

    m_stream << "body, html {\n";
    m_stream << "background: #000000;\n";
    m_stream << "width: " << width << "px;\n";
    m_stream << "font-size: 16px;\n";
    m_stream << "color: #C0C0C0;\n";
    m_stream << "}\n";

    m_stream << "h1 {\n";
    m_stream << "color : #FFFFFF;\n";
    m_stream << "border-bottom : 1px dotted #888888;\n";
    m_stream << "}\n";

    m_stream << "pre {\n";
    m_stream << "margin : 0;\n";
    m_stream << "}\n";

    m_stream << ".box {\n";
    m_stream << "border : 1px dotted #818286;\n";
    m_stream << "padding : 5px;\n";
    m_stream << "margin: 5px;\n";
    m_stream << "width: " << width << "px;\n";
    m_stream << "background-color : #292929;\n";
    m_stream << "}\n";

    m_stream << ".err {\n";
    m_stream << "color: #EE1100;\n";
    m_stream << "font-weight: bold\n";
    m_stream << "}\n";

    m_stream << ".warn {\n";
    m_stream << "color: #FFCC00;\n";
    m_stream << "font-weight: bold\n";
    m_stream << "}\n";

    m_stream << ".info {\n";
    m_stream << "color: #C0C0C0;\n";
    m_stream << "}\n";

    m_stream << ".debug {\n";
    m_stream << "color: #CCA0A0;\n";
    m_stream << "}\n";

    m_stream << ".havok {\n";
    m_stream << "color: #3399FF;\n";
    m_stream << "}\n";

    m_stream << "</style>\n";
    m_stream << "</head>\n\n";

    m_stream << "<body>\n";
    m_stream << "<h1>" << logTitle << "</h1>\n";

    struct   tm   *tmNow;   
    time_t   long_time;   
    time(&long_time);
    tmNow = localtime(&long_time);
    m_stream << "<h3>" << asctime(tmNow) << "</h3>\n";
    m_stream << "<div class=\"box\">\n";
    m_stream << "<table>\n";

    m_stream.flush();
    g_logInited = true;

    return true;
}

void Log::destroy()
{
    hkCriticalSectionLock _l(&g_CS);
    m_stream << "</table>\n";
    m_stream << "</div>\n";
    m_stream << "</body>\n";
    m_stream << "</html>";
    m_stream.close();
}

void Log::log( int logLevel, const char* msg, ...)
{
    if(!g_logInited) return;

    hkCriticalSectionLock _l(&g_CS);
    va_list argp;
    va_start(argp, msg);
    vsprintf_s(g_logBuffer, msg, argp);
    va_end(argp);

    const char* tag = g_loglevelTag[logLevel];
    printf("%s:%s.\n",tag, g_logBuffer);

    m_stream << "<tr>\n";
    m_stream << "<td width=\"50\">";
    
    SYSTEMTIME lt;
    GetLocalTime(&lt);
    char timeBuf[32];
    sprintf_s(timeBuf, "[%02d:%02d:%02d::%02d]", lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds);

    m_stream << timeBuf;
    m_stream << "</td>\n";
    m_stream << "<td class=\"";
    m_stream << tag;

    m_stream << "\"><pre>\n";
    m_stream << g_logBuffer;
    m_stream << "\n</pre></td>\n";
    m_stream << "</tr>\n";

    m_stream.flush();
    
    if(g_webServerTool) g_webServerTool->on_log_message(logLevel, g_logBuffer);

    if(logLevel >= LOG_LEVEL_WARNING) 
    {
        OutputDebugStringA(g_logBuffer);
        OutputDebugStringA("\n");
    }
}

TimeAutoLog::TimeAutoLog(const char* msg, ...)
{
    m_time = ::GetTickCount();
    va_list argp;
    va_start(argp, msg);
    vsprintf_s(m_buffer, msg, argp);
    va_end(argp);
    LOGI("===============%s started....===============", m_buffer);
}

TimeAutoLog::~TimeAutoLog()
{
    DWORD dwTime = ::GetTickCount() - m_time;
    LOGI("===============%s time cost : %d (msec)===============", m_buffer, dwTime);
}
