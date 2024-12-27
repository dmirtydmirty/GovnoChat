#include "../Include/ChatService.h"
#include <iostream>

void ChatService::add_user(std::shared_ptr<Session> new_user){
    uint32_t id = new_user->getId();
    m_users.emplace(id, new_user);
}

void ChatService::send_message(const Message& msg){
    // for(const user)
}
