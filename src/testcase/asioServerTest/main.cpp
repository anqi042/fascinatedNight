
#include "mySocket.hpp"
#include "logger.hpp"
using boost::asio::ip::tcp;

int main(){
    loggertest();
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
