#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

class Printer{
    public:
        Printer(boost::asio::io_service& asio_serv):timer_(asio_serv, boost::posix_time::seconds(1)),count_(0){
            timer_.async_wait(boost::bind(&Printer::print,this));

        }

        void print(){
            if (count_ < 5){
                timer_.expires_at(timer_.expires_at()+boost::posix_time::seconds(1));
                timer_.async_wait(boost::bind(&Printer::print,this));
                count_++;
            }
        }
    private:
        int count_;
        boost::asio::deadline_timer timer_;

};


void print(const boost::system::error_code&, boost::asio::deadline_timer* t, int* count ){
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
    boost::asio::io_service io;
    Printer printer(io);
    boost::thread th1(other_work);
    io.run();
    return 0;
}
