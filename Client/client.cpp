#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

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


int main(int argc, char **argv)
{
//    QApplication app(argc, argv);
//
//    QLabel* label = new QLabel("GovnoChat client");
//
//    QTextEdit textEdit;
//    QPushButton quitButton("Send");
//    QObject::connect(&quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
//    QVBoxLayout layout;
//    layout.addWidget(&textEdit);
//    layout.addWidget(&quitButton);
//    layout.addWidget(label);
//
//    QWidget window;
//    window.setLayout(&layout);
//
//    window.show();
//
//    return app.exec();
}