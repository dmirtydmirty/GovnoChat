#ifndef IMESSAGE
#define IMESSAGE

#include <string>
#include <any>
#include <nlohmann/json.hpp>

class IMessage{
public:
    IMessage(){}

    virtual std::any get() const = 0;

};


#endif