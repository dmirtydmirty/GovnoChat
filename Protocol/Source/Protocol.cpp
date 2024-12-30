#include "../Include/Protocol.h"
#include <iostream>

std::string Protocol::pack_message(const Message& msg){
    std::string msg_packed;
    switch (msg.m_type)
    {
    case MessageType::FROM_USER:
        msg_packed = USER_MSG_MARKER + DELIMITER + "User" + std::to_string(msg.m_sender) + ":" + msg.m_content;
        std::cout << msg_packed;
        break;
    
    case MessageType::FROM_SERVER:
        msg_packed = SERVER_MSG_MARKER + DELIMITER + msg.m_content;
        std::cout << msg_packed;
        break;
    }
    return msg_packed;
}

Message Protocol::create_message(std::string msg, u_int32_t sender_id){
    return Message(msg, sender_id, sender_id == 0 ? MessageType::FROM_SERVER : MessageType::FROM_USER);
} 