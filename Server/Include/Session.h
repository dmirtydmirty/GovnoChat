#ifndef SESSION
#define SESSION

#include <boost/asio.hpp>
#include <memory>

class Session: public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::ip::tcp::socket&& socket);
    void send(std::string msg);
    void receive();
    void start(std::function<void(std::string, uint32_t)>&& on_message);
    uint32_t getId() const {return id;}
private:
    static inline uint32_t id_ctr{0};
    uint32_t id;
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> messages;
    std::function<void(std::string, uint32_t)> message_handler;
};

#endif