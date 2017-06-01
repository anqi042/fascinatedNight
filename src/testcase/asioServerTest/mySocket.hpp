#include <ctime>
#include <memory>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include  <utility>

using boost::asio::ip::tcp;

class tcp_socket{
    public:
        typedef boost::shared_ptr<tcp_socket> tcp_socket_ptr;
        static tcp_socket_ptr create(boost::asio::io_service& io_service){
            return tcp_socket_ptr(new tcp_socket(io_service));
        }
        tcp::socket& get_sock(){
            return socket_;
        }

    private:
        tcp_socket(boost::asio::io_service& io_service): socket_(io_service){
        }
        tcp::socket socket_;

};


void do_accept_(const boost::system::error_code&){
    std::cout << "Oh" << std::endl;
}

class tcp_server{
    public:
        tcp_server(int port,boost::asio::io_service& io_service):acceptor_(io_service,tcp::endpoint(tcp::v4(),port)){
            do_accept();
            //auto newconnection = tcp_socket::create(acceptor_.get_io_service());
            //acceptor_.async_accept(newconnection->get_sock(),&tcp_server::handle_accept,this);
        }
        void do_accept(){
            auto newconnection = tcp_socket::create(acceptor_.get_io_service());
            acceptor_.async_accept(newconnection->get_sock(),boost::bind(&tcp_server::handle_accept,this));
        }

        void handle_accept(){
            std::cout << "welcome" << std::endl;
            do_accept();
        }

    private:
        tcp::acceptor acceptor_;
};
