#include "../Include/Packet.h"

using namespace nlohmann::literals;

Packet::Packet(const std::string& raw_packet){
    if (!nlohmann::json::accept(raw_packet))
        throw std::runtime_error("Incorrect packet format");

    nlohmann::json packet_json = nlohmann::json::parse(raw_packet);

    try{
        this->m_sender = packet_json.at("Sender").get<uint32_t>();
        this->m_type = static_cast<MessageType>(packet_json.at("Type").get<uint32_t>());

        switch (this->m_type)
        {
        case MessageType::USER_MESSAGE :
            this->m_message = std::make_shared<UserMessage>(packet_json.at("Message").template get<UserMessage>());
            break;
        case MessageType::USER_ID_NOTIFICATION :
            this->m_message = std::make_shared<UserIDNotification>(packet_json.at("Message").template get<UserIDNotification>());
            break;
        case MessageType::SERVER_STATUS_MESSAGE :
            this->m_message = std::make_shared<ServerStatusMessage>(packet_json.at("Message").template get<ServerStatusMessage>());
            break;   
        default:
            throw std::runtime_error("Unknown message type");
            break;
        }
    }
    catch (const nlohmann::json::exception& err){
        throw std::runtime_error(err.what());
    }
    
}

Packet::Packet(const std::shared_ptr<IMessage>& msg, MessageType type, uint32_t sender) : 
            m_type(type),
            m_sender(sender),
            m_message(msg){
}

std::string Packet::pack() const{
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