#include "../Include/Protocol.h"
#include <iostream>

std::string Protocol::pack_message(const Message& msg){
    std::stringstream msg_packed;
    nlohmann::json msg_json;

    msg_json["Type"] = static_cast<uint8_t>(msg.m_type);
    msg_json["Sender"] = msg.m_sender;
    msg_json["Content"] = msg.m_content;
    msg_packed << msg_json;

    return msg_packed.str();
}


Message Protocol::parse_message(std::string raw_message){
    std::string content{};
    uint32_t sender{};
    MessageType type{};

 
    try {
        nlohmann::json msg_json{nlohmann::json::parse(raw_message)};
        content = msg_json["Content"];
        sender = msg_json["Sender"];
        type = msg_json["Type"];
    }
    catch(nlohmann::json::parse_error& err){
        throw std::runtime_error("Invalid message format");
    }
    return Message(content, sender, type); 
}
    