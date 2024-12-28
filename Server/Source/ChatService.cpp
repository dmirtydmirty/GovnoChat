#include "../Include/ChatService.h"
#include <iostream>

void ChatService::add_user(std::shared_ptr<Session> new_user){
    uint32_t id = new_user->getId();
    m_users.emplace(id, new_user);
    std::cout << "Registred new user id: " << new_user->getId() << std::endl;
}

void ChatService::send_message(const Message& msg){
     for(const auto& user: m_users){
        if (user.first != msg.get_user_id())
            user.second->send(m_protocol->pack_message(msg));
     }
}


void ChatService::delete_user(uint32_t id){
    m_users.erase(id);
    std::cout << "User with id: " << id << " has been deleted" << std::endl;
}