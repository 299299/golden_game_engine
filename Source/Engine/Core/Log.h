#pragma once
#include <fstream>

enum LogLevel
{
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL,
    LOG_LEVEL_FATAL,
    LOG_LEVEL_HAVOK,
    LOG_LEVEL_INVALID
};

#define USER_LOG
#ifdef USER_LOG
#define LOGI(...)               gLogger.log(LOG_LEVEL_INFO, __VA_ARGS__);
#define LOGE(...)               gLogger.log(LOG_LEVEL_ERROR, __VA_ARGS__);
#define LOGW(...)               gLogger.log(LOG_LEVEL_WARNING, __VA_ARGS__);
#define LOGD(...)               gLogger.log(LOG_LEVEL_DEBUG, __VA_ARGS__);
#define LOGHAVOK(...)           gLogger.log(LOG_LEVEL_HAVOK, __VA_ARGS__);
#define LOG_INIT(fileName, title) gLogger.init(fileName, title);
#define LOG_TERM()              gLogger.destroy();
#else
#define LOGI(...)               __noop;
#define LOGE(...)               __noop;
#define LOGW(...)               __noop;
#define LOGD(...)               __noop;
#define LOGHAVOK(...)           __noop;
#define LOG_INIT(fileName)      __noop;
#define LOG_TERM()              __noop;
#endif

class Log 
{
public:
    Log();
    ~Log();
    bool init(const char* logFile, const char* logTitle);
    void destroy();
    void log(int logLevel, const char* msg, ...);
private:
    std::ofstream                   m_stream;
};


extern Log gLogger;

#ifdef USER_LOG
#define TIMELOG(...)    TimeAutoLog _log(__VA_ARGS__);
#else
#define TIMELOG(...)    __noop;
#endif

class TimeAutoLog
{
public:
    TimeAutoLog(const char* msg, ...);
    ~TimeAutoLog();
private:
    char                    m_buffer[1024];
    size_t                  m_time;
};