#ifndef CHAT_SERVICE
#define CHAT_SERVICE

#include <map>
#include <memory>

#include "Session.h"
#include "../../Protocol/Include/Protocol.h"
#include "../../Protocol/Include/Packet.h"

class ChatService
{
public:
    ChatService(){}
    void add_user(std::shared_ptr<Session> new_user);
    void delete_user(uint32_t id);
    void send_packet(const Packet& packet);
    bool validate_message(const std::string& content, uint32_t sender_id) = delete;
private:
    std::map<uint32_t, std::shared_ptr<Session>> m_users;
};





#endif