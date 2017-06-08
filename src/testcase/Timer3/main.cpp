#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

void print(const boost::system::error_code&, boost::asio::deadline_timer* t, int* count ){
    if (*count < 5){
        t->expires_at(t->expires_at()+boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print,boost::asio::placeholders::error,t,count));
        std::cout << "Hello,world" << std::endl;
        ++*count;
    }
}

void print_no_err_para(boost::asio::deadline_timer* t, int* count ){
    if (*count < 5){
        t->expires_at(t->expires_at()+boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print,boost::asio::placeholders::error,t,count));
        std::cout << "Hello,world" << std::endl;
        ++*count;
    }
}

void other_work(){
    while(1){
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        std::cout << "..." << std::endl;
    }
}

int main(){
    int count = 0;
    int count2 = 0;
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    boost::asio::deadline_timer t2(io, boost::posix_time::seconds(1));
    t.async_wait(boost::bind(print,boost::asio::placeholders::error,&t,&count));
    t2.async_wait(boost::bind(print_no_err_para,&t2,&count2));
    //start a thread for other_work
    boost::thread th1(other_work);


    io.run();
    return 0;
}
