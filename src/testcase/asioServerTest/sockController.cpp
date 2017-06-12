#include "sockController.hpp"
#include "brain.hpp"
void Connection::readCallBack(char* msg_buffer,size_t n){
    int res = -1;
    if(isHead){
        if (n != BigDickMsg::HEADLEN){
            //fucked!
        }else{
            res = dick_for_read.decode_head(msg_buffer);
            if (res == -1){
                //fucked!close connection
                //erase it from connList_,check if alive
                //close it
                LOG(INFO) << "Wrong Header ";
                if(tcp_socket_->isAlive()){
                    if(tcp_socket_->close()){
                        LOG(INFO) << "close this pipe ";
                    }else{
                        LOG(ERROR) << "close failed" ;
                    }
                }
            }else{
                LOG(INFO) << "head is ok, read " << res << " bytes ";
                isHead = false;
                tcp_socket_->do_read_nbytes(res);

            }
        }
    }else{
        //receive message body
        LOG(INFO) << "message received";
        isHead = true;
        dick_for_read.encode_msg_buff_only(msg_buffer,n);
        //enqueue a copy
        Brain::getInstance()->msg_enqueue(dick_for_read);
        //clear
        std::memset(dick_for_read.data,0,BigDickMsg::TOTALLEN);
        tcp_socket_->do_read_nbytes(BigDickMsg::HEADLEN);
    }
    //tcp_socket_->do_write_nbytes(msg_buffer ,n);
}


void Connection::writeCallBack(){

    LOG(INFO) << "write call back";
}


void Server::acceptCallBack(tcp::socket sock){
    LOG(INFO) << "accept call back";
    std::shared_ptr<Connection> connPtr(new Connection(std::move(sock)));
    //connList_.push_back(connPtr);
    Brain::getInstance()->attach_connec(connPtr);
    connPtr->start();
    tcp_server_.do_accept();

}
