#ifndef CTRL_HEADER_FILE_H
#define CTRL_HEADER_FILE_H
#include <array>
#include "msg_head.hpp"
#include "mySocket.hpp"
#include <utility>
#include <functional>
using std::placeholders::_1;
using boost::asio::ip::tcp;
class Connection{
    public:
        Connection(tcp::socket sock):tcp_socket_(tcp_socket::create(std::move(sock),
            std::bind(&Connection::readCallBack,this,std::placeholders::_1,std::placeholders::_2),
            std::bind(&Connection::writeCallBack,this))){

            auto remote_ep = tcp_socket_->get_sock().remote_endpoint();
            auto remote_ad = remote_ep.address();
            std::string str_addr = remote_ad.to_string();
            LOG(INFO) << str_addr  <<" is accepted ";
        }
        void start(){
            LOG(INFO) << "Connection start..";
            //read ...
            tcp_socket_->do_read_nbytes(5);
        }
    private:
        void readCallBack(char*,size_t n);
        void writeCallBack();
        tcp_socket::tcp_socket_ptr tcp_socket_;
};



class Server{
    public:
        typedef boost::shared_ptr<Connection> ConnPtrType ;
        Server(int port,boost::asio::io_service& io_service):
            tcp_server_(port,io_service,std::bind(&Server::acceptCallBack,this,std::placeholders::_1)){
            LOG(INFO) << "Server init";
            tcp_server_.do_accept();
        }

    private:
        void acceptCallBack(tcp::socket sock);
        tcp_server tcp_server_;
        std::vector<ConnPtrType> connList_;

};


#endif