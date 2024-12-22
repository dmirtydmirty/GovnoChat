#ifndef SERVER
#define SERVER

#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <map>

#include "Session.h"

class Server {
public:
    Server(boost::asio::io_context& io_context, std::uint16_t port);
    void start();
    void stop();
    void deleteSessionById(uint32_t id);
private:
    void asyncAccept();
    void createSession();
    void post(std::string msg);
    void sendAll(std::string msg, uint32_t senderId);
    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
    std::map<uint32_t, std::shared_ptr<Session>> clients;
};

#endif