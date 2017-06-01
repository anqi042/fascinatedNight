#include "mySocket.hpp"
using boost::asio::ip::tcp;

void do_accept(const boost::system::error_code&){
    std::cout << "Oh" << std::endl;
}
void simple_test(){
    boost::asio::io_service  io_service;
    auto newconnection = tcp_socket::create(io_service);
    tcp::acceptor acceptor_(io_service,tcp::endpoint(tcp::v4(),999));
    acceptor_.async_accept(newconnection->get_sock(),&do_accept);
    io_service.run();
}



int main(){
    try{
    boost::asio::io_service  io_service;
    tcp_server  server(666,io_service);
    io_service.run();
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
