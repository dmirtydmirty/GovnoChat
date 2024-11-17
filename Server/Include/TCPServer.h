#ifndef TCP_SERVER
#define TCP_SERVER

#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <unordered_set>

#include "Session.h"

class TCPServer {
public:
    TCPServer(boost::asio::io_context& io_context, std::uint16_t port);
    void start();
private:
    void async_accept();
    void post(std::string msg);
    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
    std::unordered_set<std::shared_ptr<Session>> clients;
};

#endif