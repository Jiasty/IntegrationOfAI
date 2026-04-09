#include "LLMProvider.h"


namespace ChatSDK
{
    class DeepSeekProvider : public LLMProvider
    {
    public:
        virtual ~DeepSeekProvider() = default;

        // 初始化模型
        virtual bool InitModel(const std::map<std::string, std::string>& modelConfig) override;
        // 判断模型是否有效
        virtual bool IsAvailable() const override;
        // 获取模型名称
        virtual std::string GetModelName() const override;
        // 获取模型描述
        virtual std::string GetModelDescription() const override;
        // 发送消息--全量返回
        virtual std::string SendMessage(const std::vector<Message>& messages, const std::map<std::string, std::string>& options) override;
        // 发送消息--流式返回
        virtual std::string SendMessageStream(const std::vector<Message>& messages,
                                              const std::map<std::string, std::string>& options,
                                              std::function<void(const std::string&, bool)> callback) override;
    };
}


