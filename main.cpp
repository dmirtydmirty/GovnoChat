#include <boost/asio.hpp>
#include <iostream>

#include "Server/Include/Server.h"

int main(int argc, char *argv[]) {
    boost::asio::io_context io_context;
    TCPServer srv(io_context, 15001);
    srv.async_accept();
    io_context.run();
    return 0;
}