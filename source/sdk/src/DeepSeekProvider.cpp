#include "../include/DeepSeekProvider.h"
#include "../include/Util/MyLog.h"
#include <jsoncpp/json/json.h>  // TODO: jsoncpp库的使用
#include <httplib.h>  // TODO: cpp-httplib库的使用


namespace ChatSDK
{
    bool DeepSeekProvider::InitModel(const std::map<std::string, std::string>& modelConfig)
    {   
        // 初始化API key
        auto it = modelConfig.find("apiKey");
        if(it == modelConfig.end())
        {
            // TODO: Jiasty_Log域指定吗?
            LOG_ERROR("DeepSeekProvider InitModel failed: apiKey is missing in modelConfig");
            return false;
        }
        else
        {
            _apiKey = it->second;
        }

        // 初始化endpoint  Base URL
        it = modelConfig.find("endpoint");
        if(it == modelConfig.end())
        {
            LOG_ERROR("DeepSeekProvider InitModel failed: endpoint is missing in modelConfig"); 
            return false;
        }
        else
        {
            _endpoint = it->second;
        }

        _isAvailable = true;  // TODO: 可以增加一些API调用来验证API Key和Endpoint的有效性
        LOG_INFO("DeepSeekProvider InitModel success: apiKey and endpoint are set");
        return true;
    }

    bool DeepSeekProvider::IsAvailable() const
    {
        return _isAvailable;
    }

    std::string DeepSeekProvider::GetModelName() const
    {
        return "deepseek-chat";  // TODO: 可以从配置中获取更具体的模型名称
    }

    std::string DeepSeekProvider::GetModelDescription() const
    {
        return "DeepSeek提供的聊天模型, 支持文本生成和对话功能";  // TODO: 可以从配置中获取更具体的模型描述
    }

    std::string DeepSeekProvider::SendMessage(const std::vector<Message>& messages, const std::map<std::string, std::string>& requestParams)
    {
        // 1.检测模型是否可用
        if(!_isAvailable)
        {
            LOG_ERROR("DeepSeekProvider SendMessage failed: model is not available");
            return "";
        }
        
        // 2.构造请求参数(模型名称、消息列表、温度值、maxTokens、是否开启流式响应等)
        float temperature = 0.7;  // 默认温度值
        int maxTokens = 2048;    // 默认最大生成令牌数

        auto it = requestParams.find("temperature");
        if(it != requestParams.end())
            temperature = std::stof(it->second);  // 将字符串转换为浮点数
        it = requestParams.find("maxTokens");
        if(it != requestParams.end())
            maxTokens = std::stoi(it->second);  // 将字符串转换为整数

        // ------------------TODO-----------------
        // 构造消息列表(历史消息 + 当前消息)  
        Json::Value messageArray(Json::arrayValue);
        for(const auto& msg : messages)
        {
            Json::Value messageJson;
            messageJson["role"] = msg._role;
            messageJson["content"] = msg._content;
            messageArray.append(messageJson);
        }

        // 3.构造请求体
        Json::Value requestBody;
        requestBody["model"] = GetModelName();
        requestBody["messages"] = messageArray;
        requestBody["temperature"] = temperature;
        requestBody["max_tokens"] = maxTokens;

        // 4.序列化
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder["indentation"] = "";  // 去掉默认的缩进和换行，使输出更紧凑
        std::string requestBodyStr = Json::writeString(writerBuilder, requestBody);
        LOG_INFO("DeepSeekProvider SendMessage request body: {}", requestBodyStr.c_str());

        // 5.使用cpp-httplib库构造HTTP客户端
        httplib::Client cli(_endpoint.c_str());
        cli.set_connection_timeout(30);   // 设置连接超时时间为30秒
        cli.set_read_timeout(60);         // 设置读取超时时间为30秒

        // 设置请求头


        // 6.发送HTTP POST请求


        return "";
    }

    std::string DeepSeekProvider::SendMessageStream(const std::vector<Message>& messages,
                                              const std::map<std::string, std::string>& options,
                                              std::function<void(const std::string&, bool)> callback)
    {
        // 构造消息列表(历史消息 + 当前消息)

    }

}  // end namespace ChatSDK