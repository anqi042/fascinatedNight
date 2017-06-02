
#include "mySocket.hpp"
#include "glog.hpp"
using boost::asio::ip::tcp;

void init(char* argv[]){
     FLAGS_logbufsecs = 0;
     FLAGS_log_dir = "./debug_log";
    google::InitGoogleLogging(argv[0]);
     LOG(INFO) << "Hello World";
}



int main(int argc,char* argv[]){
    init(argv);
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
