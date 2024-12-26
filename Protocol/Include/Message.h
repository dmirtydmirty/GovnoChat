#ifndef MESSAGE
#define MESSAGE

#include <string>

enum MessageType{
    FROM_SERVER,
    FROM_USER,
};

class Message{
public:
    Message();
private:
    std::string m_content;
    std::string m_sender;
    MessageType m_type;
};


#endif