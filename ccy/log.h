#ifndef CCY_LOG_H
#define CCY_LOG_H

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <strstream>
#include <fstream>
#include <iostream>

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

    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;

    void setFormatter(LogFormatter::ptr val) {m_formatter = val;}
    LogFormatter::ptr  getFormatter() const {return m_formatter;}

protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
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

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender); 
    void delAppender(LogAppender::ptr appender); 
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level val) {m_level = val;}

private:
    std::string m_name;                             // log name
    LogLevel::Level m_level;                        // log level
    std::list<LogAppender::ptr> m_appenders;        //  list of Appender
};

// output to console
class ConsoleLogAppender: public LogAppender {
public:
    typedef std::shared_ptr<ConsoleLogAppender> ptr;
    void log(LogLevel::Level level, LogEvent::ptr event) override;
};

// output to file
class FileLogAppender: public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(LogLevel::Level level, LogEvent::ptr event) override;
    
// reopen file, if open successfully, return true
    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

}

#endif