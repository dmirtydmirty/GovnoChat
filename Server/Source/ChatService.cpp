#include "../Include/ChatService.h"
#include <iostream>

void ChatService::add_user(std::shared_ptr<Session> new_user){
    uint32_t id = new_user->get_id();
    m_users.emplace(id, new_user);
    auto notif = std::make_shared<UserIDNotification>(id);
    Packet packet(notif, USER_ID_NOTIFICATION, Protocol::SERVER_ID);
    new_user->send(packet.pack());
    std::cout << "Registred new user id: " << id << std::endl;
}

void ChatService::send_message(const Message& msg){
    for(const auto& user: m_users) {
        if (user.first != msg.get_sender())
            user.second->send(m_protocol->pack_message(msg));
    }
}

void ChatService::delete_user(uint32_t id){
    m_users.erase(id);
    std::cout << "User with id: " << id << " has been deleted" << std::endl;
}
