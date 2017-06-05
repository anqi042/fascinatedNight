#include <ctime>
#include <memory>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include  <utility>
#include "msg_head.hpp"
#include "glog.hpp"
#include <vector>
using boost::asio::ip::tcp;

class tcp_socket{
    public:
        typedef boost::shared_ptr<tcp_socket> tcp_socket_ptr;
        static tcp_socket_ptr create(tcp::socket socket){
            return tcp_socket_ptr(new tcp_socket(std::move(socket)));
        }
        tcp::socket& get_sock(){
            return socket_;
        }
        //invoke handler when n bytes are read
        void do_read_nbytes(size_t n){
            boost::asio::async_read(socket_,boost::asio::buffer(msg_buffer_,n),boost::bind(&tcp_socket::handle_read,this,
                        boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
        }

        void handle_read(const boost::system::error_code& ec,
                    std::size_t bytes_transferred);



        void start(){
            do_read_nbytes(5);
        }
    private:
        tcp_socket(tcp::socket socket): socket_(std::move(socket)){
        }
        tcp::socket socket_;

        std::array<char,MAX_MSG_LEN> msg_buffer_;
};



class tcp_server{
    public:
        tcp_server(int port,boost::asio::io_service& io_service):listen_sock_(io_service),acceptor_(io_service,tcp::endpoint(tcp::v4(),port)){
            do_accept();
        }
        void do_accept(){
            acceptor_.async_accept(listen_sock_,boost::bind(&tcp_server::handle_accept,this,
                        boost::asio::placeholders::error));

        }

    private:
        void handle_accept(const boost::system::error_code& ec);

        tcp::acceptor acceptor_;
        tcp::socket listen_sock_;
        std::vector<tcp_socket::tcp_socket_ptr> connections_;
};
