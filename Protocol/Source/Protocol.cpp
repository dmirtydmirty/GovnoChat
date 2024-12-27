#include "../Include/Protocol.h"

std::string Protocol::pack_message(Message msg){
    std::string msg_packed;
    switch (msg.m_type)
    {
    case MessageType::FROM_USER:
        msg_packed = USER_MSG_MARKER + DELIMITER + "USER" + std::to_string(msg.m_sender) + ":" + msg.m_content;
        break;
    
    case MessageType::FROM_SERVER:
        msg_packed = USER_MSG_MARKER + DELIMITER + msg.m_content;
        break;
    }
    return msg_packed;
}

Message Protocol::create_message(std::string msg, u_int32_t sender_id){
    return Message(msg, sender_id, sender_id == 0 ? MessageType::FROM_SERVER : MessageType::FROM_USER);
} 