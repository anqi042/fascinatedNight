#ifndef CTRL_HEADER_FILE_H
#define CTRL_HEADER_FILE_H
#include <list>
#include <array>
#include "msgStruct.hpp"
#include "mySocket.hpp"
#include <utility>
#include <functional>
#include <memory>
using std::placeholders::_1;
using boost::asio::ip::tcp;
class Connection:public std::enable_shared_from_this<Connection>{
    public:
        Connection(tcp::socket sock):isHead(true),
            tcp_socket_(tcp_socket::create(std::move(sock),
            std::bind(&Connection::readCallBack,this,std::placeholders::_1,std::placeholders::_2),
            std::bind(&Connection::writeCallBack,this))){

            auto remote_ep = tcp_socket_->get_sock().remote_endpoint();
            auto remote_ad = remote_ep.address();
            std::string str_addr = remote_ad.to_string();
            LOG(INFO) << str_addr  <<" is accepted ";
        }
        void start(){
            LOG(INFO) << "Connection start..";
            tcp_socket_->do_read_nbytes(BigDickMsg::HEADLEN);
        }

        inline bool isAlive(){
            return tcp_socket_->isAlive();
        }
    private:
        void readCallBack(char*,size_t n);
        void writeCallBack();
        void processLogin();
        BigDickMsg dick_for_read;
        BigDickMsg dick_for_write;
        tcp_socket::tcp_socket_ptr tcp_socket_;
        volatile int isHead;
};



class Server{
    public:
        typedef std::shared_ptr<Connection> ConnPtrType ;
        Server(int port,boost::asio::io_service& io_service):
            tcp_server_(port,io_service,std::bind(&Server::acceptCallBack,this,std::placeholders::_1)){
            LOG(INFO) << "Server init";
            tcp_server_.do_accept();
        }

    private:
        void acceptCallBack(tcp::socket sock);
        tcp_server tcp_server_;

};


#endif
