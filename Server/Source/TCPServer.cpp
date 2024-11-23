#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <unordered_set>
#include <memory>

#include "../Include/TCPServer.h"
#include "../Include/Session.h"

TCPServer::TCPServer(boost::asio::io_context& io_context, std::uint16_t port) :
        io_context(io_context),
        acceptor(
                io_context,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

void TCPServer::start(){
    std::cout << "Sarting TCP server " << std::endl; 
    acceptor.listen();
    std::cout << "Serever listens the port: " << this->acceptor.local_endpoint().port() << std::endl;
    this->async_accept();
}

void TCPServer::async_accept() {
    socket.emplace(io_context);
    acceptor.async_accept(*socket, [&](boost::system::error_code error) {
        std::cout << "New connection from " << socket->remote_endpoint() << std::endl;
        std::string new_client = socket->remote_endpoint().address().to_string() + ":" +
                            std::to_string(socket->remote_endpoint().port());
        post(new_client + " is connected\n\r");
        auto new_session= std::make_shared<Session>(std::move(*socket));
        new_session->start(std::bind(&TCPServer::sendAll, this, std::placeholders::_1, std::placeholders::_2));
        clients.insert(new_session);
        std::cout << "Created new session id: " << new_session->getId() << std::endl;
        async_accept();
    });
}


void TCPServer::post(std::string msg){
    for (auto client: clients) {
        client->send(msg);
    }
}
void TCPServer::sendAll(std::string msg,  uint32_t senderId){
    for (auto client: clients) {
        if (client->getId() != senderId)
            client->send(msg);
    }
}