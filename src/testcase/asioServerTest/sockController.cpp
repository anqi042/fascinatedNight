#include "sockController.hpp"
void Connection::readCallBack(char* msg_buffer,size_t n){
    LOG(INFO) << "read call back";
    tcp_socket_->do_read_nbytes(5);
    tcp_socket_->do_write_nbytes(msg_buffer ,n);
}


void Connection::writeCallBack(){

    LOG(INFO) << "write call back";
}


void Server::acceptCallBack(tcp::socket sock){
    LOG(INFO) << "accept call back";
    boost::shared_ptr<Connection> connPtr(new Connection(std::move(sock)));
    connList_.push_back(connPtr);
    connPtr->start();
    tcp_server_.do_accept();

}
