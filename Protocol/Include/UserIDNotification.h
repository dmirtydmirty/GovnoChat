#ifndef USERIDNOTIFICATION
#define USERIDNOTIFICATION

#include <string>

#include "IMessage.h"


class UserIDNotification :  virtual public IMessage {
public:

UserIDNotification(uint32_t id):  m_id(id) {}


std::any get() const {return m_id;}

private:
    uint32_t m_id;

    friend class nlohmann::adl_serializer<UserIDNotification>;

};


namespace nlohmann
{
template <>
struct adl_serializer<UserIDNotification>
{
    static UserIDNotification from_json(const json& j){
        return UserIDNotification(j.at("ID").get<uint32_t>());
    }

    static void to_json(json& j, UserIDNotification p)
    {
        j["ID"] = p.m_id;
    }
};
}


#endif