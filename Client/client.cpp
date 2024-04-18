#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

void client(){
    std::uint16_t port = 15001;

    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket(io_context);
    boost::asio::ip::udp::endpoint serv(boost::asio::ip::address_v4(), port);
    socket.open(boost::asio::ip::udp::v4());
    while (true) {
        std::string buffer;
        std::cout << "TO SERVER: ";
        getline(std::cin, buffer);
        socket.send_to(boost::asio::buffer(buffer), serv);
        socket.receive_from(boost::asio::buffer(buffer), serv);
        std::cout << "FROM SERVER: " << buffer << std::endl;

    }
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget widget;
    widget.setWindowTitle("You have a trojan");
    widget.setMinimumHeight(180);
    widget.setMinimumWidth(300);

    QLabel label{&widget};
    label.setText("You have a virus, dolboeb");

    widget.show();
    return app.exec();
    return 0;
}