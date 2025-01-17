#ifndef IMESSAGE
#define IMESSAGE

#include <string>

#include "Protocol.h"

enum MessageType : uint8_t {
    USER_MESSAGE=0,

    USER_ID_NOTIFICATION=1,
    SERVER_INFO=2,
};

class IMessage{
public:

    MessageType get_type() const {return m_type;}
    uint32_t get_sender() const {return m_sender;}

    virtual std::string pack() const = 0;

private:

    virtual void validate(std::string raw_message) = 0;

    u_int32_t m_sender;
    MessageType m_type;
    std::string m_content;

};


#endif