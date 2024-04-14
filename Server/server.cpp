#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>

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
                }

            });
    }

    void start() {
        boost::asio::async_read_until(
            socket,
            streambuf,
            '\n',
            [self = shared_from_this()](
                boost::system::error_code error,
                std::size_t bytes_transferred) {
                if (error){
                    std::cerr << error.message() << std::endl;
                }
                std::cout << "RECEIVED: " << std::istream(&self->streambuf).rdbuf();
//                self->send_to_client("Welcome to the GovnoChat");
//                self->messages.push_back(self->streambuf.);
            });
    }



  private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> messages;
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
//            std::make_shared<session>(std::move(*socket))->start();
            auto new_session= std::make_shared<session>(std::move(*socket));
            new_session->start();
            clients.push_back(new_session);
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
    std::vector<std::shared_ptr<session>> clients;
};

int main() {
    boost::asio::io_context io_context;
    server srv(io_context, 15001);
    srv.async_accept();
    io_context.run();
    return 0;
}