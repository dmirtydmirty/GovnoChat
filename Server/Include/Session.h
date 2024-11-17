#ifndef SESSION
#define SESSION

#include <boost/asio.hpp>
#include <memory>

class Session: public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::ip::tcp::socket&& socket);
    void send(std::string msg);
    void receive();
    void start(std::function<void(std::string)>&& on_message);
private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> messages;
    std::function<void(std::string)> message_handler;
};

#endif