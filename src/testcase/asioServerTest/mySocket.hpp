#ifndef SOCKET_HEADER_FILE_H
#define SOCKET_HEADER_FILE_H
#include <functional>
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
        typedef std::function<void(std::array<char,MAX_MSG_LEN>,size_t)> ReadCBObj;
        typedef std::function<void()> WriteCBObj;
        typedef boost::shared_ptr<tcp_socket> tcp_socket_ptr;

        static tcp_socket_ptr create(tcp::socket socket,ReadCBObj r,WriteCBObj w){
            return tcp_socket_ptr(new tcp_socket(std::move(socket),r,w));
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


        void do_write_nbytes(std::array<char,MAX_MSG_LEN> writebuffer,size_t n){
            boost::asio::async_write(socket_, boost::asio::buffer(writebuffer, n),
            boost::bind(&tcp_socket::handle_write,
            this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred) );
        }

        void handle_write( const boost::system::error_code& ec,std::size_t bytes_transferred);

        void start(){
            do_read_nbytes(5);
        }
    private:
        tcp_socket(tcp::socket socket,ReadCBObj rObj,WriteCBObj wObj): socket_(std::move(socket)),
        readCallBackObj_(rObj),writeCallBackObj_(wObj)
        {
        }

        tcp::socket socket_;

        std::array<char,MAX_MSG_LEN> msg_buffer_;

        ReadCBObj  readCallBackObj_;
        WriteCBObj writeCallBackObj_;
};



class tcp_server{
    public:
        typedef std::function<void(tcp::socket)> accCallBackObj;
        tcp_server(int port,boost::asio::io_service& io_service,accCallBackObj fObj):listen_sock_(io_service),
        acceptor_(io_service,tcp::endpoint(tcp::v4(),port)),
        accCallBackObj_(fObj)
        {
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
        //must need a space to store shared_ptr, or it will
        //dead when outof the range of function
        std::vector<tcp_socket::tcp_socket_ptr> connections_;
        //object store accecpt handler
        std::function<void(tcp::socket)> accCallBackObj_;
};




#endif
