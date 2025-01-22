#ifndef SERVERSTATUSMESSAGE
#define SERVERSTATUSMESSAGE

#include <string>

#include "IMessage.h"


class ServerStatusMessage :  virtual public IMessage {
public:

ServerStatusMessage(const std::string& status_info): m_status_info(status_info) {}

std::any get() const {return m_status_info;}

private:
    std::string m_status_info;


    friend class nlohmann::adl_serializer<ServerStatusMessage>;

};


namespace nlohmann
{
template <>
struct adl_serializer<ServerStatusMessage>
{
    static ServerStatusMessage from_json(const json& j){
        return ServerStatusMessage(j.at("StatusInfo").get<std::string>());
    }

    static void to_json(json& j, ServerStatusMessage p)
    {
        j["StatusInfo"] = p.m_status_info;
    }
};
}


#endif