#include <memory>
#include <limits.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>                     // TODO
#include <spdlog/sinks/basic_file_sink.h>     // TODO
#include <spdlog/sinks/stdout_color_sinks.h>  // TODO


#include "../../include/Util/MyLog.h"

// namespace Jiasty_Log等价于Jiasty_Log::
namespace Jiasty_Log
{
    // static成员初始化或定义时要去掉static，防止被解释为该成员只能在本文件使用
    std::shared_ptr<spdlog::logger> _logger = nulltr;
    std::mutex _mutex;

    void Logger::InitLogger(const std::string& loggerName, const std::string& loggerFile, spdlog::level::level_enum logLevel)
    {
        if(nullptr == _logger)  // TODO: 是等于空指针，还是不等于nullptr？ --- IGNORE ---
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if(nullptr == _logger)
            {
                // 设置全局自动刷新级别，当日志级别 >= logLevel 时，日志会被立即刷新到文件
                spdlog::flush_on(logLevel);

                // 启用异步日志，即将日志信息存放队列中，有后台线程负责写入
                // 参数1: 队列大小，参数2: 后台线程数量
                spdlog::init_thread_pool(SHRT_MAX, 1);
                if("stdout" == loggerFile)  // 输出到标准输出流 
                {
                    // 创建一个带颜色的输出到控制台的日志器
                    _logger = spdlog::stdout_color_mt(loggerName);
                }else
                {
                    //创建一个文件输出的日志器，日志会被写入到指定的文件中
                    _logger = spdlog::basic_logger_mt<spdlog::async_logger>(loggerName, loggerFile);
                }
            }
        }

        // 格式设置
        // [%Y-%m-%d %H:%M:%S]: 输出年月日时分秒
        // [%.7l]: 输出日志级别，左对齐且占7个字符宽度，不足部分用空格填充
        // %v: 输出日志消息内容
        _logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%.7l] %v");
        // 设置日志级别，只有日志级别 >= logLevel 的日志才会被记录
        _logger->set_level(logLevel);
    }

    std::shared_ptr<spdlog::logger> Logger::GetLogger()
    {
        return _logger;
    }
}