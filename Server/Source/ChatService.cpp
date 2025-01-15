#include "../Include/ChatService.h"
#include <iostream>

void ChatService::add_user(std::shared_ptr<Session> new_user){
    uint32_t id = new_user->get_id();
    m_users.emplace(id, new_user);
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

void ChatService::send_use_id_responce(const Message& msg){
    auto response =  Message(std::to_string(msg.get_sender()), 0, MessageType::USER_ID_RESPONSE);
    for(const auto& user: m_users){
        if (user.first == msg.get_sender()) // откуда там правильный id если он взят из сообщения
        // а юзер его не знает, надо отправлять эту фигню сразу как юзер подключается, пока у нас есть прямой доступ к сессии, не по id
            user.second->send(m_protocol->pack_message(response));
     }
}