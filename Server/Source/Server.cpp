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
        acceptor(std::make_unique<Acceptor>(io_context, port, std::bind(&Server::handle_accept, this, std::placeholders::_1)))
        {}
        catch (const boost::system::system_error & err){
            std::cout << "TCPServer::TCPServer: an error " << err.code() << " occured: "<< err.what() << std::endl;
        }

void Server::start(){
    std::cout << "Starting TCP server " << std::endl; 
    acceptor->start_accept();
}

void Server::stop(){
    io_context.stop();
}

void Server::handle_message(const std::string& raw_message, uint32_t sender_id){
    std::cout << "Server::handle_message() handling message from user" << sender_id << std::endl;
    try{
        Packet packet(raw_message);

        MessageType type = packet.get_type();
        switch (type) {
            case MessageType::USER_MESSAGE:
                service.send_packet(packet);
            break;
        }
    }
    catch(const std::runtime_error& err){
        std::cerr << "Server::handle_message() Handlig error: " << err.what() << std::endl;
    }
}

void Server::handle_disconnect(uint32_t sender_id){
    service.delete_user(sender_id);
    std::string msg = "User" + std::to_string(sender_id) + " disconnected";
    auto status = std::make_shared<ServerStatusMessage>(msg);
    service.send_packet(Packet(status, MessageType::SERVER_STATUS_MESSAGE, Protocol::SERVER_ID));
}

void Server::handle_accept(boost::asio::ip::tcp::socket&& sock){
    auto new_session = std::make_shared<Session>(std::move(sock),
                std::bind(&Server::handle_message,      this, std::placeholders::_1, std::placeholders::_2),
                std::bind(&Server::handle_disconnect,   this, std::placeholders::_1));
    std::string msg = "User" + std::to_string(new_session->get_id()) + " is connected";
    auto status = std::make_shared<ServerStatusMessage>(msg);
    service.send_packet(Packet(status, MessageType::SERVER_STATUS_MESSAGE, Protocol::SERVER_ID));
    new_session->start();
    service.add_user(std::move(new_session));

}
