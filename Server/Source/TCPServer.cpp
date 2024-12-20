#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <map>
#include <memory>

#include "../Include/TCPServer.h"
#include "../Include/Session.h"

TCPServer::TCPServer(boost::asio::io_context& io_context, std::uint16_t port) try:
        io_context(io_context),
        acceptor(
                io_context,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}
        catch (const boost::system::system_error & err){
            std::cout << "TCPServer::TCPServer: an error " << err.code() << " occured: "<< err.what() << std::endl;
        }

void TCPServer::start(){
    std::cout << "Sarting TCP server " << std::endl; 
    acceptor.listen();
    std::cout << "Serever listens the port: " << this->acceptor.local_endpoint().port() << std::endl;
    this->asyncAccept();
}

void TCPServer::stop(){
    io_context.stop();
}

void TCPServer::asyncAccept() {
    socket.emplace(io_context);
    acceptor.async_accept(*socket, [&](boost::system::error_code error) {

        if (error){
            std::cout << "Accept failed with code: " << error.value() << " " << error.message() << std::endl;
            stop();
        }
        std::cout << "New connection from " << socket->remote_endpoint() << std::endl;
        createSession();
        asyncAccept();
    });
}

void TCPServer::createSession(){
    std::stringstream msg;
        msg << Session::SERVER_MSG_MARKER << Session::DELIMITER << socket->remote_endpoint() << " is connected\n\r";
        post(msg.str());
        auto new_session= std::make_shared<Session>(std::move(*socket));
        new_session->start(std::bind(&TCPServer::sendAll, this, std::placeholders::_1, std::placeholders::_2),
                            std::bind(&TCPServer::deleteSessionById, this, new_session->getId()));
        std::cout << "New session created id: " << new_session->getId() << std::endl;
        clients.insert({new_session->getId(), std::move(new_session)});
}

void TCPServer::post(std::string msg){
    for (auto client: clients) {
        client.second->send(msg);
    }
}

void TCPServer::sendAll(std::string msg,  uint32_t senderId){
    for (auto client: clients) {
        if (client.second->getId() != senderId)
            client.second->send(msg);
    }
}

void TCPServer::deleteSessionById(uint32_t id){
    clients.erase(id);
}