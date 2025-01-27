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

void ChatService::send_packet(const Packet& packet){
    for(const auto& user: m_users) {
        if (user.first != packet.get_sender())
            user.second->send(packet.pack());
    }
}

void ChatService::delete_user(uint32_t id){
    m_users.erase(id);
    std::cout << "User with id: " << id << " has been deleted" << std::endl;
}
