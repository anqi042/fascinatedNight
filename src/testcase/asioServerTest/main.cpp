#include "sockController.hpp"
#include "brain.hpp"
#include "glog.hpp"
#include <memory>
using boost::asio::ip::tcp;

void init(char* argv[]){
    char * dirname= "logdir";
    mklogdir(dirname);
     FLAGS_logbufsecs = 0;
     FLAGS_log_dir = dirname;
    google::InitGoogleLogging(argv[0]);
     LOG(INFO) << "Hello World";
}



int main(int argc,char* argv[]){
    init(argv);
    try{
        boost::asio::io_service  io_service;
        std::shared_ptr<Server> server(new Server(666,io_service));
        auto brain = Brain::getInstance(server);
        //Server server(666,io_service);
        io_service.run();
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
