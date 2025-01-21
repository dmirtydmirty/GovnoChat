#include "../Include/Packet.h"
#include "../Include/UserMessage.h"
#include "../Include/UserIDNotification.h"
#include "../Include/ServerStatusMessage.h"

Packet::Packet(const std::string& raw_packet){
    if (nlohmann::json::accept(raw_packet))
        throw std::runtime_error("Incorrect packet format");

    nlohmann::json packet_json{nlohmann::json::parse(raw_packet)};

    if (!packet_json["Sender"].is_number_integer())
        throw std::runtime_error("Incorrect packet content");

    if (!packet_json["Type"].is_number_integer())
        throw std::runtime_error("Incorrect packet content");

    if (!packet_json["Message"].is_object())
        throw std::runtime_error("Incorrect packet content");

    this->m_sender = packet_json["Sender"].get<uint32_t>();
    this->m_type = static_cast<MessageType>(packet_json["Type"].get<uint32_t>());

    switch (this->m_type)
    {
    case MessageType::USER_MESSAGE :
        this->m_message = std::make_unique<UserMessage>(packet_json["Sender"].template get<UserMessage>());
        break;
    case MessageType::USER_ID_NOTIFICATION :
        this->m_message = std::make_unique<UserIDNotification>(packet_json["Sender"].template get<UserIDNotification>());
        break;
    case MessageType::SERVER_STATUS_MESSAGE :
        this->m_message = std::make_unique<ServerStatusMessage>(packet_json["Sender"].template get<ServerStatusMessage>());
        break;   
    default:
        throw std::runtime_error("Unknown message type");
        break;
    }
    
}


std::string Packet::pack(){
    nlohmann::json packet_json;
    packet_json["Sender"] = this->m_sender;
    packet_json["Type"] = static_cast<uint8_t>(this->m_type);


    switch (this->m_type)
    {
    case MessageType::USER_MESSAGE :
        packet_json["Message"] = nlohmann::json(*dynamic_cast<UserMessage*>(m_message.get())); 
        break;
    case MessageType::SERVER_STATUS_MESSAGE :
        packet_json["Message"] = nlohmann::json(*dynamic_cast<ServerStatusMessage*>(m_message.get())); 
        break;
    case MessageType::USER_ID_NOTIFICATION :
        packet_json["Message"] = nlohmann::json(*dynamic_cast<UserIDNotification*>(m_message.get())); 
        break;
    default:
        throw std::runtime_error("Unknown message type");
        break;
    }

    return packet_json.dump(4);
}