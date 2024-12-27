#include "../Include/Session.h"
#include "../Include/Server.h"
#include <iostream>


Session::Session(boost::asio::ip::tcp::socket socket) :
        socket(std::move(socket)) {
            this->id = id_ctr++;
}

void Session::send(std::string&& msg){
    boost::asio::async_write(
        socket, boost::asio::buffer(msg),
        [self = this, &msg](
            boost::system::error_code error,
            size_t bytes_transferred){
            std::cout << "Send " << msg << " to user" << self->getId() << std::endl;  
            if (error){
                std::stringstream msg;
                self->message_handler(msg.str(), self->getId());
                self->disconnect_handler();
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
            std::cout << "New message from user" << self->getId() << std::endl;
            if (error){
                std::stringstream msg;
                std::cout << msg.str();
                self->message_handler(msg.str(), self->getId());
                self->disconnect_handler();
                return;
            }
            std::stringstream message;
            self->message_handler(std::move(message.str()), self->getId());
            self->receive();
        });
}
void Session::start(std::function<void(std::string, uint32_t)>&& on_message,
                std::function<void()>&& on_disconnect) {
    this->message_handler = on_message;
    this->disconnect_handler = on_disconnect;
    this->receive();
}