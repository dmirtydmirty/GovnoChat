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
    acceptor.listen(1);
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
        new_session->start(std::bind(&TCPServer::post, this, std::placeholders::_1));
        clients.insert(new_session);
        async_accept();
    });
}

void TCPServer::post(std::string msg){
    for (auto client: clients) {
        client->send(msg);
    }
}