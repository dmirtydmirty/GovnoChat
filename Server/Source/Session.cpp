#include "../Include/Session.h"
#include <iostream>


Session::Session(boost::asio::ip::tcp::socket&& socket) :
        socket(std::move(socket)) {
            this->id = id_ctr++;
}

void Session::send(std::string msg){
    boost::asio::async_write(
        socket, boost::asio::buffer(msg),
        [self = shared_from_this()](
            boost::system::error_code error,
            size_t bytes_transferred){
            if (error){
                std::stringstream msg;
                msg << self->socket.remote_endpoint() << " was disconnected" << std::endl;
                std::cout << msg.str();
                self->message_handler(msg.str(), self->getId());
        }
    });
}

void Session::receive(){
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
                self->message_handler(msg.str(), self->getId());
                return;
            }
            std::stringstream message;
            message << self->socket.remote_endpoint() << ": " << std::istream(&self->streambuf).rdbuf();
            self->message_handler(message.str(), self->getId());
            self->receive();
        });
}
void Session::start(std::function<void(std::string, uint32_t)>&& on_message) {
    this->message_handler=on_message;
    this->send("Welcome to chat, dolboeb\n\r");
    this->receive();
}