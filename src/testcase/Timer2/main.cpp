#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

void print(const boost::system::error_code& ){
    std::cout << "Hello,world" << std::endl;
}

void other_work(){
    while(1){
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        std::cout << "..." << std::endl;
    }
}

int main(){
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.async_wait(&print);
    //start a thread for other_work
    boost::thread t1(other_work);


    io.run();
    return 0;
}
