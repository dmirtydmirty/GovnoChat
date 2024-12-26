#ifndef PROTOCOL
#define PROTOCOL

#include <string>

#include "Message.h"

class Protocol{
public:
    Protocol() = default;

    std::string build_message(Message msg);

    Message parse_message(std::string msg);
private:
    static inline std::string USER_MSG_MARKER   = "USERMSG";
    static inline std::string SERVER_MSG_MARKER = "SERVERMSG";
    static inline std::string DELIMITER         = "///";  


};


#endif