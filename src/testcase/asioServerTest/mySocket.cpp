#include "mySocket.hpp"
#include "brain.hpp"

void tcp_socket::handle_read(const boost::system::error_code& ec,
        std::size_t bytes_transferred){

    if(!ec){
        readCallBackObj_(msg_buffer_,bytes_transferred);
    }else {
        //if error is operation cancelled,socket has been closed ;
        //this occurs when using netcat or unfriendly client
        std::cout << ec.value() << " " << ec.message() <<std::endl;
        if (ec.value() == 2){// end of file
            LOG(INFO) << "peer endpoint disconnected; close socket";
           //socket_.close();
        }

    }

}


void tcp_server::handle_accept(const boost::system::error_code& ec){
    accCallBackObj_(std::move(listen_sock_));
}

void tcp_socket::handle_write( const boost::system::error_code& ec,std::size_t bytes_transferred){
    writeCallBackObj_();
}
