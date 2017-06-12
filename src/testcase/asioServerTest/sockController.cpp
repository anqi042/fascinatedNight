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
                tcp_socket_->do_read_nbytes(dick_for_read.msg_body_len_);

            }
        }
    }else{
        //receive message body
        isHead = true;
        dick_for_read.encode_msg_buff_only(msg_buffer,n);
        if(dick_for_read.msg_type_==BigDickMsg::LOGIN_TYPE){
            processLogin();

        }else if(dick_for_read.msg_type_ == BigDickMsg::MSG_TYPE){
            //enqueue a copy
            Brain::getInstance()->msg_enqueue(dick_for_read);

        }
        //clear
        std::memset(dick_for_read.data,0,BigDickMsg::TOTALLEN);
        tcp_socket_->do_read_nbytes(BigDickMsg::HEADLEN);
    }
    //tcp_socket_->do_write_nbytes(msg_buffer ,n);
}

void Connection::processLogin(){
    if(dick_for_read.msg_type_ == BigDickMsg::LOGIN_TYPE){
            LOG(INFO) << dick_for_read.get_my_id()<< " Login!";
        Brain::getInstance()->set_user2connec(
                dick_for_read.get_my_id(),shared_from_this()
                );
    }
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
