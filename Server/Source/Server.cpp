#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <map>
#include <memory>

#include "../Include/Server.h"
#include "../Include/Session.h"

Server::Server(boost::asio::io_context& io_context, std::uint16_t port) try:
        io_context(io_context),
        acceptor(std::make_unique<Acceptor>(io_context, port, std::bind(&Server::handle_accept, this, std::placeholders::_1))),
        protocol(),
        service(std::shared_ptr<Protocol>(protocol)) {}
        catch (const boost::system::system_error & err){
            std::cout << "TCPServer::TCPServer: an error " << err.code() << " occured: "<< err.what() << std::endl;
        }

void Server::start(){
    std::cout << "Sarting TCP server " << std::endl; 
    acceptor->start_accept();
}

void Server::stop(){
    io_context.stop();
}

void Server::handle_message(const std::string& content, uint32_t sender_id){
    std::cout <<  "handling message from user" << sender_id << std::endl;
    Message msg = protocol->create_message(content, sender_id);
    service.send_message(msg);
}

void Server::handle_disconnect(uint32_t sender_id){
    service.delete_user(sender_id);
    std::string msg = "User" + std::to_string(sender_id) + " disconnected\n\r";
    service.send_message(Message(msg, SERVER_ID, MessageType::FROM_SERVER));
}

void Server::handle_accept(boost::asio::ip::tcp::socket&& sock){
    auto new_session = std::make_shared<Session>(std::move(sock));
    std::string msg = "User" + std::to_string(new_session->getId()) + " is connected\n\r";
    service.send_message(Message(msg, SERVER_ID, MessageType::FROM_SERVER));
    new_session->start(std::bind(&Server::handle_message, this, std::placeholders::_1, std::placeholders::_2),
                        std::bind(&Server::handle_disconnect, this, new_session->getId()));
    service.add_user(std::move(new_session));

}
