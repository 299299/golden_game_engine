#include "Log.h"
#include <stdarg.h>
#include <time.h>
#include "DataDef.h"
#include "Prerequisites.h"
#include <bx/debug.h>
#include <bx/mutex.h>

static bool                 g_logInited = false;
static char                 g_logBuffer[4096*2];
static unsigned long        g_startTime = 0;
static bx::LwMutex          g_logLock;
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

Log g_logger;

Log::Log()
{

}

Log::~Log()
{

}

bool Log::init( const char* logFile, const char* logTitle)
{
    bx::LwMutexScope _l(g_logLock);
    g_startTime = ::GetTickCount();
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
    bx::LwMutexScope _l(g_logLock);
    m_stream << "</table>\n";
    m_stream << "</div>\n";
    m_stream << "</body>\n";
    m_stream << "</html>";
    m_stream.close();
}

void Log::log( int logLevel, const char* msg, ...)
{
    if(!g_logInited) return;

    bx::LwMutexScope _l(g_logLock);
    va_list argp;
    va_start(argp, msg);
    vsnprintf(g_logBuffer, sizeof(g_logBuffer), msg, argp);
    va_end(argp);

    const char* tag = g_loglevelTag[logLevel];
    printf("%s:%s.\n",tag, g_logBuffer);

    m_stream << "<tr>\n";
    m_stream << "<td width=\"50\">";

    m_stream << GetTickCount();
    m_stream << "</td>\n";
    m_stream << "<td class=\"";
    m_stream << tag;

    m_stream << "\"><pre>\n";
    m_stream << g_logBuffer;
    m_stream << "\n</pre></td>\n";
    m_stream << "</tr>\n";

    m_stream.flush();

    if(logLevel >= LOG_LEVEL_WARNING)
    {
        bx::debugOutput(g_logBuffer);
        bx::debugOutput("\n");
    }
}


TimeAutoLog::TimeAutoLog(const char* msg, ...)
{
    m_time = ::GetTickCount();
    va_list argp;
    va_start(argp, msg);
    vsnprintf(m_buffer, sizeof(m_buffer), msg, argp);
    va_end(argp);
    LOGI("===============%s started....===============", m_buffer);
}

TimeAutoLog::~TimeAutoLog()
{
    unsigned long dwTime = ::GetTickCount() - m_time;
    LOGI("===============%s time cost : %d (msec)===============", m_buffer, dwTime);
}
