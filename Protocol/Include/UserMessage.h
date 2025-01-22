#ifndef USERMESSAGE
#define USERMESSAGE

#include <string>

#include "IMessage.h"


class UserMessage :  virtual public IMessage {
public:

UserMessage(const std::string& content): m_content(content) {}

std::any get() const {return m_content;}

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
        return UserMessage(j.at("Content").get<std::string>());
    }

    static void to_json(json& j, UserMessage p)
    {
        j["Content"] = p.m_content;
    }
};
}


#endif