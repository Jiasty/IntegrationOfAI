#ifndef _SDK_MYLOG_H_
#define _SDK_MYLOG_H_

#include <memory>
#include <spdlog/spdlog.h>

namespace Jiasty_Log
{
    //////使用单例模式封装spdlog实现日志类//////
    class Logger
    {
    public:
        // REVIEW: spdlog::level::level_enum
        static void InitLogger(const std::string &loggerName, const std::string &loggerFile, spdlog::level::level_enum logLevel = spdlog::level::info);
        static std::shared_ptr<spdlog::logger> GetLogger();

    private:
        Logger();
        // 形参在函数内部不会被用到，通常就省掉
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

    private:
        static std::shared_ptr<spdlog::logger> _logger;  // 使用shared_ptr是因为一个日志器可以对应多个...使用
        static std::mutex _mutex;                        // 互斥锁，保证线程安全
        // REVIEW: static、spdlog
    };

    // TODO: fmt库的格式化字符串语法，https://fmt.dev/latest/syntax.html
    // string s = format("The answer is {}.", 42);  有点像python的f-string，{}是占位符，后面的参数会依次替换掉占位符
    // s == "The answer is 42."
    #define LOG_TRACE(format, ...)  Jiasty_Log::Logger::GetLogger()->trace(std::string("[{:>10s}:{:<4d}]") + format, __FILE__, __LINE__, ##__VA_ARGS__)
    #define LOG_DBG(format, ...)  Jiasty_Log::Logger::GetLogger()->debug(std::string("[{:>10s}:{:<4d}]") + format, __FILE__, __LINE__, ##__VA_ARGS__)
    #define LOG_INFO(format, ...)  Jiasty_Log::Logger::GetLogger()->info(std::string("[{:>10s}:{:<4d}]") + format, __FILE__, __LINE__, ##__VA_ARGS__)
    #define LOG_WARN(format, ...)  Jiasty_Log::Logger::GetLogger()->warn(std::string("[{:>10s}:{:<4d}]") + format, __FILE__, __LINE__, ##__VA_ARGS__)
    #define LOG_ERROR(format, ...)  Jiasty_Log::Logger::GetLogger()->error(std::string("[{:>10s}:{:<4d}]") + format, __FILE__, __LINE__, ##__VA_ARGS__)
    #define LOG_CRITICAL(format, ...)  Jiasty_Log::Logger::GetLogger()->critical(std::string("[{:>10s}:{:<4d}]") + format, __FILE__, __LINE__, ##__VA_ARGS__)

} // end namespace Jiasty_Log

#endif