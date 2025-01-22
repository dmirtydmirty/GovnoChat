#ifndef MESSAGE
#define MESSAGE

#include <string>

#include "Protocol.h"
#include "Packet.h"

class Message{
public:
    Message(const std::string& content, u_int32_t sender, MessageType type):
        m_content(content), m_sender(sender), m_type(type){
        };

    MessageType get_type() const {return m_type;}
    uint32_t get_sender() const {return m_sender;}
private:
    std::string m_content;
    u_int32_t m_sender;
    MessageType m_type;

    friend class Protocol;
};


#endif