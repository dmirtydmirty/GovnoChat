#ifndef MESSAGE
#define MESSAGE

#include <string>

#include "Protocol.h"

enum MessageType{
    FROM_SERVER,
    FROM_USER,
};

class Message{
public:
    Message(const std::string& content, u_int32_t sender, MessageType type):
        m_content(content), m_sender(sender), m_type(type){
        };
    u_int32_t get_user_id() const {return m_sender;}
private:
    std::string m_content;
    u_int32_t m_sender;
    MessageType m_type;

    friend class Protocol;
};


#endif