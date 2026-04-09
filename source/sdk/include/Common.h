#ifndef _SDK_COMMON_H_
#define _SDK_COMMON_H_

#include <string>
#include <vector>
#include <ctime> // REVIEW


namespace ChatSDK
{
    // 消息结构
    struct Message
    {
        Message(std::string role, std::time_t timestamp)
            : _role(role)
            , _timestamp(timestamp)
        {}

        std::string _messageId;  // 消息ID
        std::string _role;       // 角色(用户、AI的各种角色等)
        std::string _content;    // 消息内容
        std::time_t _timestamp;  // 消息的发送时间戳  // REVIEW: 时间戳
    };


    // 各种模型的公共配置信息
    struct Config
    {
        std::string _name;
        float _temprature = 0.7;  // 温度参数，控制文本随机性，越大越随机
        int _maxTokens = 2048;    // 最大生成令牌(Token)数
    };

    // 通过API方式接入云端大模型
    struct ApiConfig : public Config
    {
        std::string _apiKey;  // 本地接入不需要API Key，每个平台的API Key不一样
    };

    // 通过Ollama接入本地大模型--不需要API Key
    struct OllamaConfig : public Config
    {
        std::string _modelPath;  // 本地模型路径
    };

    // LLM信息
    struct ModelInfo
    {
    public:
        ModelInfo(std::string name = "", std::string desc = "", std::string provider = "", std::string endpoint = "")
            : _name(name)
            , _desc(desc)
            , _provider(provider)
            , _endpoint(endpoint)
        {}

        std::string _name; 
        std::string _desc;          // 模型信息描述
        std::string _provider;      // 模型提供者
        std::string _endpoint;      // 模型API endpoint  base url
        bool _isAvaliable = false;  // 模型是否可用
    };

    // 会话信息
    struct Session
    {
        Session(std::string modelName)
            : _modelName(modelName)
        {}

        std::string _sessionId;
        std::string _modelName;          // 会话使用的模型名称
        std::vector<Message> _messages;  // 会话中的消息列表
        std::time_t _createAt;           // 会话创建时间戳
        std::time_t _updateAt;           // 最近信息时间戳
    };
    
}  // end namespace ChatSDK 


#endif