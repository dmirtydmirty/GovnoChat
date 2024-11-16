#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <unordered_set>
#include <memory>

#include "../Include/Server.h"


Session::Session(boost::asio::ip::tcp::socket&& socket) :
        socket(std::move(socket)) {}

void Session::async_write(std::string msg){
    boost::asio::async_write(
        socket, boost::asio::buffer(msg),
        [self = shared_from_this()](
            boost::system::error_code error,
            size_t bytes_transferred){
            if (error){
                std::stringstream msg;
                msg << self->socket.remote_endpoint() << " was disconnected" << std::endl;
                std::cout << msg.str();
                self->message_handler(msg.str());
        }
    });
}

void Session::async_read(){
    boost::asio::async_read_until(
        socket,
        streambuf,
        '\n',
        [self = shared_from_this()](
            boost::system::error_code error,
            std::size_t bytes_transferred) {
            if (error){
                std::stringstream msg;
                msg << self->socket.remote_endpoint() << " was disconnected" << std::endl;
                std::cout << msg.str();
                self->message_handler(msg.str());
                return;
            }
            std::stringstream message;
            message << self->socket.remote_endpoint() << ": " << std::istream(&self->streambuf).rdbuf();
            self->message_handler(message.str());
            self->async_read();
        });
}
void Session::start(std::function<void(std::string)>&& on_message) {
    this->message_handler=on_message;
    this->async_read();
}

TCPServer::TCPServer(boost::asio::io_context& io_context, std::uint16_t port) :
        io_context(io_context),
        acceptor(
                io_context,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

void TCPServer::async_accept() {
    socket.emplace(io_context);
    acceptor.async_accept(*socket, [&](boost::system::error_code error) {
        std::cout << "New connection from " << socket->remote_endpoint() << std::endl;
        std::string new_client = socket->remote_endpoint().address().to_string() + ":" +
                            std::to_string(socket->remote_endpoint().port());
        post(new_client + " is connected\n\r");
        auto new_session= std::make_shared<Session>(std::move(*socket));
        new_session->start(std::bind(&TCPServer::post, this, std::placeholders::_1));
        new_session->async_write("Welcome to chat, dolboeb\n\r");
        clients.insert(new_session);
        async_accept();
    });
}

void TCPServer::post(std::string msg){
    for (auto client: clients) {
        client->async_write(msg);
    }
}