#ifndef SERVER
#define SERVER

#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <map>

#include "Session.h"
#include "../../Protocol/Include/Protocol.h"
#include "ChatService.h"
#include "Acceptor.h"

class Server {
public:
    Server(boost::asio::io_context& io_context, std::uint16_t port);
    void start();
    void stop();
private:
    void handle_message(const std::string& raw_message, uint32_t sender_id);
    void handle_disconnect(uint32_t sender_id);
    void handle_accept(boost::asio::ip::tcp::socket&& sock);

    boost::asio::io_context& io_context;
    ChatService service;
    std::unique_ptr<Acceptor> acceptor;
};

#endif