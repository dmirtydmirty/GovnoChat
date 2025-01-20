#ifndef USERMESSAGE
#define USERMESSAGE

#include <string>

#include "IMessage.h"


class UserMessage :  virtual public IMessage {
public:

UserMessage(const std::string& content): IMessage(content), m_content(content) {}

private:
    std::string m_content;

    friend class nlohmann::adl_serializer<UserMessage>;

};


namespace nlohmann
{
template <>
struct adl_serializer<UserMessage>
{
    static UserMessage from_json(const json& j){
        return {j.at("Content")};
    }

    static void to_json(json& j, UserMessage p)
    {
        j["Content"] = p.m_content;
    }
};
}


#endif