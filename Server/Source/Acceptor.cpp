#include "../Include/Acceptor.h"
#include <iostream>

Acceptor::Acceptor(boost::asio::io_service& ios, int port, accept_handler handler) :
    m_ios(ios), 
    m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port)),
    acception_handler(handler)
{}

void Acceptor::start_accept(){
    m_acceptor.listen();
    std::cout << "Start listening port: " << this->m_acceptor.local_endpoint().port() << std::endl;
    async_accept();
}

void Acceptor::async_accept(){
    boost::asio::ip::tcp::socket sock(m_ios);
    m_acceptor.async_accept(sock, [this, &sock](boost::system::error_code code){
        this->on_accept(code, sock);
    });
}


void Acceptor::on_accept(const boost::system::error_code& code, boost::asio::ip::tcp::socket& sock){

    if (code.value() != 0){
        std::cerr << "Acception error: " << code.what() << " code: " << code.value() << std::endl;
    }

    std::cout << "New imcoming connection with: " << sock.remote_endpoint() <<  std::endl;
    acception_handler(std::move(sock));
    async_accept();
}