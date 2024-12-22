#include <boost/asio.hpp>
#include <iostream>

#include "Server/Include/Server.h"

int main(int argc, char *argv[]) {
    boost::asio::io_context io_context;
    try {
    Server srv(io_context, 15001);
    srv.start();
    io_context.run();
    }
    catch (const boost::system::system_error & err){
        std::cout << "main: an error " << err.code() << " occured: "<< err.what() << std::endl;
    }
    return 0;
}