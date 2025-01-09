#ifndef PROTOCOL
#define PROTOCOL

#include <string>
#include <nlohmann/json.hpp>

#include "Message.h"

class Protocol{
public:
    Protocol() = default;

    std::string pack_message(const Message&  msg);

    Message create_message(std::string msg, u_int32_t sender_id = 0);

    Message parse_message(std::string raw_message);
private:
    static inline std::string USER_MSG_MARKER   = "USERMSG";
    static inline std::string SERVER_MSG_MARKER = "SERVERMSG";
};

#endif