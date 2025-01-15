#ifndef PROTOCOL
#define PROTOCOL

#include <string>
#include <nlohmann/json.hpp>

#include "Message.h"

class Protocol{
public:
    Protocol() = default;

    std::string pack_message(const Message&  msg);

    Message parse_message(const std::string& raw_message);

};

#endif