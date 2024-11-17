#include <boost/asio.hpp>
#include <iostream>

#include "Server/Include/TCPServer.h"

int main(int argc, char *argv[]) {
    boost::asio::io_context io_context;
    TCPServer srv(io_context, 15001);
    srv.start();
    io_context.run();
    return 0;
}