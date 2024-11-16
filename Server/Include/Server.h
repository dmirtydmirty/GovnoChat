#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <unordered_set>

class Session: public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::ip::tcp::socket&& socket);
    void async_write(std::string msg);
    void async_read();
    void start(std::function<void(std::string)>&& on_message);
private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> messages;
    std::function<void(std::string)> message_handler;
};

class TCPServer {
public:
    TCPServer(boost::asio::io_context& io_context, std::uint16_t port);
    void async_accept();
    void post(std::string msg);
private:
    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
    std::unordered_set<std::shared_ptr<Session>> clients;
};

