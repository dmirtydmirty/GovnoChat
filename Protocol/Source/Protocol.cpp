#include "../Include/Protocol.h"
#include <iostream>

std::string Protocol::pack_message(const Message& msg){
    std::stringstream msg_packed;
    nlohmann::json msg_json;
    switch (msg.m_type)
    {
    case MessageType::FROM_USER:
        msg_json["Type"] = USER_MSG_MARKER;
        msg_json["Content"] = "User" + std::to_string(msg.m_sender) + ": " + msg.m_content;
        msg_packed << msg_json;
        break;
    case MessageType::FROM_SERVER:
        msg_json["Type"] = SERVER_MSG_MARKER;
        msg_json["Content"] = msg.m_content;
        msg_packed << msg_json;

        break;
    }
    return msg_packed.str();
}

Message Protocol::create_message(std::string msg, u_int32_t sender_id){
    return Message(msg, sender_id, sender_id == 0 ? MessageType::FROM_SERVER : MessageType::FROM_USER);
} 