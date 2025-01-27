#ifndef PACKET
#define PACKET

#include <string>
#include <memory>

#include "IMessage.h"
#include "UserMessage.h"
#include "UserIDNotification.h"
#include "ServerStatusMessage.h"

enum MessageType : uint8_t{
    USER_MESSAGE=0,

    USER_ID_NOTIFICATION=1,
    SERVER_STATUS_MESSAGE=2,
};

class Packet{
public:
    Packet(const std::string& raw_packet);
    Packet(const std::shared_ptr<IMessage>& msg, MessageType type, uint32_t sender);

    MessageType get_type() const {return m_type;}
    uint32_t get_sender() const {return m_sender;}
    std::string pack() const;
private:

    u_int32_t m_sender;
    MessageType m_type;
    std::shared_ptr<IMessage> m_message;

};


#endif