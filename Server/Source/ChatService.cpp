#include "../Include/ChatService.h"
#include <iostream>

void ChatService::add_user(std::shared_ptr<Session> new_user){
    uint32_t id = new_user->get_id();
    m_users.emplace(id, new_user);
    auto notification = Message(std::to_string(new_user->get_id()), 0, MessageType::USER_ID_NOTIFICATION); //  TODO: maks server ID as constant
    new_user->send(m_protocol->pack_message(notification));
    std::cout << "Registred new user id: " << new_user->get_id() << std::endl;
}

void ChatService::send_message(const Message& msg){
     for(const auto& user: m_users){
        if (user.first != msg.get_sender())
            user.second->send(m_protocol->pack_message(msg));
     }
}


void ChatService::delete_user(uint32_t id){
    m_users.erase(id);
    std::cout << "User with id: " << id << " has been deleted" << std::endl;
}
