#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <unordered_set>

class session: public std::enable_shared_from_this<session> {
public:
    session(boost::asio::ip::tcp::socket&& socket) :
            socket(std::move(socket)) {}

    void async_write(std::string msg){
        boost::asio::async_write(
            socket, boost::asio::buffer(msg),
            [](
                boost::system::error_code error,
                size_t bytes_transferred){
                if (error){
                std::cerr << error.message() << std::endl;
            }
        });
    }
    void async_read(){
        boost::asio::async_read_until(
            socket,
            streambuf,
            '\n',
            [self = shared_from_this()](
                boost::system::error_code error,
                std::size_t bytes_transferred) {
                if (error){
                    std::cerr << error.message() << std::endl;
                    return;
                }
                std::stringstream message;
                message << self->socket.remote_endpoint() << ": " << std::istream(&self->streambuf).rdbuf();
                self->message_handler(message.str());
                self->async_read();
            });
    }

    void start(std::function<void(std::string)>&& on_message) {
        this->message_handler=on_message;
        this->async_read();
    }



  private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> messages;
    std::function<void(std::string)> message_handler;
};

class server {
public:
    server(boost::asio::io_context& io_context, std::uint16_t port) :
            io_context(io_context),
            acceptor(
                    io_context,
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

    void async_accept() {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&](boost::system::error_code error) {
            std::cout << "New connection from " << socket->remote_endpoint() << std::endl;
            std::string new_client = socket->remote_endpoint().address().to_string() + ":" +
                              std::to_string(socket->remote_endpoint().port());
            post(new_client + " is connected\n\r");
            auto new_session= std::make_shared<session>(std::move(*socket));
            new_session->start(std::bind(&server::post, this, std::placeholders::_1));
            new_session->async_write("Welcome to chat, dolboeb\n\r");
            clients.insert(new_session);
            async_accept();
        });
    }
   void post(std::string msg){
        for (auto client: clients) {
            client->async_write(msg);
        }
    }
  private:
    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
    std::unordered_set<std::shared_ptr<session>> clients;
};

int main() {
    boost::asio::io_context io_context;
    server srv(io_context, 15001);
    srv.async_accept();
    io_context.run();
    return 0;
}