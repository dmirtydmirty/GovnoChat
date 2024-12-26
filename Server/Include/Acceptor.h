#ifndef ACCEPTOR
#define ACCEPROR

#include <boost/asio.hpp>



class Acceptor{
public:
    typedef std::function<void(boost::asio::ip::tcp::socket&&)> accept_handler;
    Acceptor(boost::asio::io_service& ios, int port, accept_handler handler);
    void start_accept();

private:
    void async_accept();

    void on_accept(const boost::system::error_code& code, boost::asio::ip::tcp::socket& sock);

    boost::asio::io_service& m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
    accept_handler acception_handler;
};


#endif