#include "../Include/Session.h"
#include "../Include/Server.h"
#include <iostream>


Session::Session(boost::asio::ip::tcp::socket socket, std::function<void(const std::string&, uint32_t)>&& on_message,
                std::function<void(uint32_t)>&& on_disconnect) :
        socket(std::move(socket)),
        message_handler(on_message),
        disconnect_handler(on_disconnect) {
            this->id = id_ctr++;
}

void Session::send(const std::string& msg){
    boost::asio::async_write(
        socket, boost::asio::buffer(msg),
        [self = this, &msg](
            boost::system::error_code error,
            size_t bytes_transferred){
            if (error){
                std::stringstream msg;
                self->message_handler(msg.str(), self->get_id());
                self->disconnect_handler(self->get_id());
        }
    });
}

Session::~Session(){
    this->socket.close();
}

void Session::receive(){
    boost::asio::async_read_until(
        socket,
        streambuf,
        '\n',
        [self = this](
            boost::system::error_code error,
            std::size_t bytes_transferred) {
            if (error){
                std::stringstream msg;
                std::cout << msg.str();
                self->disconnect_handler(self->get_id());
                return;
            }
            std::cout << "New message from user" << self->get_id() << std::endl;
            std::stringstream message;
            message << std::istream(&self->streambuf).rdbuf();
            self->message_handler(std::move(message.str()), self->get_id());
            self->receive();
        });
}

void Session::start() {
    
    this->receive();
}