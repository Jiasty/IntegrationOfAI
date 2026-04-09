#pragma once
#include <functional>
#include <string>
#include <vector>
#include <map>
#include "Common.h"

namespace ChatSDK
{
    class LLMProvider
    {
    public:
        // 初始化模型, 传参用map，key-value形式，具体参数根据不同模型而定  TODO: 为何map?
        virtual bool InitModel(const std::map<std::string, std::string>& modelConfig) = 0;
        // 判断模型是否有效
        virtual bool IsAvailable() const = 0;
        // 获取模型名称
        virtual std::string GetModelName() const = 0;
        // 获取模型描述
        virtual std::string GetModelDescription() const = 0;
        // 发送消息--全量返回
        virtual std::string SendMessage(const std::vector<Message>& messages, const std::map<std::string, std::string>& options) = 0;
        // 发送消息--流式返回
        // TODO: callback参数的设计
        // callback参数设计为一个函数对象，接受两个参数：一个是模型返回的字符串内容，另一个是一个布尔值，
        // 表示是否为流式返回的结束标志。当模型返回新的内容时，回调函数会被调用，并传入最新的内容和结束标志。
        // 这样设计可以让调用者在接收到新的内容时立即处理，同时也能知道何时流式返回结束。
        virtual std::string SendMessageStream(const std::vector<Message>& messages,
                                              const std::map<std::string, std::string>& options,
                                              std::function<void(const std::string&, bool)> callback) = 0;
    
    protected:
        bool _isAvailable = false;
        std::string _apiKey;         // API密钥
        std::string _endpoint;       // 模型API的Base URL
    };

}  // end namespace ChatSDK