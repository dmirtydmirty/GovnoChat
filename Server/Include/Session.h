#ifndef SESSION
#define SESSION

#include <boost/asio.hpp>
#include <memory>

class Session{
public:
    Session(boost::asio::ip::tcp::socket socket, std::function<void(const std::string&, uint32_t)>&& on_message,
                std::function<void(uint32_t)>&& on_disconnect);
    ~Session();
    void send(const std::string& msg);
    void receive();
    void start();
    uint32_t get_id() const {return id;}
    
private:
    static inline uint32_t id_ctr{1};
    uint32_t id;
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> messages;
    std::function<void(const std::string&, uint32_t)> message_handler;
    std::function<void(uint32_t)> disconnect_handler;
};

#endif