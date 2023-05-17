#ifndef CCY_LOH_H
#define CCY_LOH_H

#include <string>
#include <stdint.h>
#include <memory>
namespace ccy{

// log event
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();

private:
    const char* m_file = nullptr;   // file name
    int32_t m_line = 0;             // line number
    uint32_t m_elapse = 0;          // the time(ms) from program start to now
    uint32_t m_threadId = 0;        // thread ID
    uint32_t m_fiberId = 0;         // fiber ID
    uint32_t m_time = 0;            // time stamp
    std::string m_content;
};

// log level
class LogLevel{
public:
    enum Level{
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
};

// logger output dest
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr; 
    virtual ~LogAppender(){}

    void log(LogLevel::Level level, LogEvent::ptr event);
private:
    LogLevel::Level m_level;
};

// the format of log
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(LogEvent::ptr event);
private:
};

// logger
class Logger{
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);
private:
    std::string m_name;
    LogLevel::Level m_level;
    LogAppender::ptr m_formatter;            
};

// output to console
class ConsoleLogAppender: public LogAppender {

};

// output to file
class FileLogAppender: public LogAppender{

};

}

#endif