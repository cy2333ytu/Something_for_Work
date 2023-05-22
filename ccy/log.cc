#include"./log.h"
#include <vector>
namespace ccy{

const char* LogLevel::toString(LogLevel::Level level){
    switch (level){
#define XX(name) \ 
    case LogLevel::name: \
    return #name; \
    break;

    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX
    default:
        return "UNKNOW";
    }
    return  "UNKNOW";  
}

Logger::Logger(const std::string& name)
    :m_name{name}{

}

void Logger::addAppender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender){
    for (auto it = m_appenders.begin(); 
            it != m_appenders.end(); ++it){
        if(*it == appender){
            m_appenders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
    if(level >= m_level){
        for(auto& i : m_appenders){
            i->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event){
    log(LogLevel::DEBUG, event);
}

void Logger::info(LogEvent::ptr event){
    log(LogLevel::INFO, event);
}

void Logger::warn(LogEvent::ptr event){
    log(LogLevel::WARN, event);
}

void Logger::error(LogEvent::ptr event){
    log(LogLevel::ERROR, event);
}

void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);
}


FileLogAppender::FileLogAppender(const std::string& filename){

}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event){
    if(level >= m_level){
        m_filestream << m_formatter->format(event);
    }
}

bool FileLogAppender::reopen(){
    if(m_filename){
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !!m_filestream;
}

void ConsoleLogAppender::log(LogLevel::Level level, LogEvent::ptr event){
    if(level > m_level){
        std::cout << m_formatter->format(event);
    }
}

LogFormatter::LogFormatter(const std::string& pattern)
    :m_pattern = pattern {
}
std::string LogFormatter::format(LogLevel::Level level, LogEvent::ptr event){
    std::stringstream ss;
    for(auto& i: m_items){
        i->format(ss, level,event);
    }
    return ss.str();
}

void LogFormatter::init(){
    std::vector<std::tuple<std::string, std::string, int>> vec;
    std::string nstr;
    for(size_t i = 0; i < m_pattern.size(); i++){
        if(m_pattern != '%'){
            nstr.append(1, m_pattern[i]);
            continue;
        }
        if((i+1) < m_pattern.size()){
            if(m_pattern == '%'){
                nstr.append(1, '%');
                continue;
        }
    }
    size_t n = i + 1;
    int fmt_status = 0
    size_t fmt_begin = 0;

    std::string str;
    std::string fmt;
    while(n < m_pattern.size()){
        if(!fmt_status && (isalpha(m_pattern[n]) && m_pattern[n] != '{'
        && m_pattern[n] != '}')){
            str = m_pattern.substr(i+1, n-i-1);
            break;
        }
        if(fmt_status == 0){
            if(m_pattern[n] == '{'){
                str = m_pattern.substr(i+1, n-i-1);
                fmt_status = 1;
                fmt_begin = n;
                ++n;
                continue;
            }
        } else if(fmt_status == 1){
            if(m_pattern[n] == '}'){
                fmt = m_pattern.substr(fmt_begin + 1, n-fmt_begin + 1);
                fmt_status = 0;
                ++n;
                break;
            }
        }
        ++n;
        if(n == m_pattern.size()){
            if(str.empty()){
                str = m_pattern.substr(i+1);
            }
        }

    }

    if(fmt_status == 0) {
    if(!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, std::string(), 0));
        nstr.clear();
    }
    vec.push_back(std::make_tuple(str, fmt, 1));
    i = n - 1;
} else if(fmt_status == 1) {
    std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << std::endl;
    m_error = true;
    vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
}
}
    if(!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }
}
     //  %m 消息
     //  %p 日志级别
     //  %r 累计毫秒数
     //  %c 日志名称
     //  %t 线程id
     //  %n 换行
     //  %d 时间
     //  %f 文件名
     //  %l 行号
class MessageFormatItem: public LogFormatter::FormatItem{
public:
    void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event) override{
        os<< event->getContent();
    }
};
class LevelFormatItem: public LogFormatter::FormatItem{
public:
    void format(std::ostream& os, LogLevel::Level level, LogFormatter::ptr event) override{
        os<<LogLevel::toString(level);
    }
};





}// ccy
