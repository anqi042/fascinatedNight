#include "mySocket.hpp"

void tcp_socket::handle_read(const boost::system::error_code& ec,
        std::size_t bytes_transferred){
    if(!ec){
        std::string msg(std::begin(msg_buffer_),std::begin(msg_buffer_)+bytes_transferred);
        std::cout << bytes_transferred << " " << msg << std::endl;

        do_read_nbytes(5);
        do_write_nbytes(msg_buffer_,5);
    }else {
        //if error is operation cancelled,socket has been closed ;
        //this occurs when using netcat or unfriendly client
        std::cout << ec.value() << " " << ec.message() <<std::endl;
        if (ec.value() == 2){// end of file
            LOG(INFO) << "peer endpoint disconnected; close socket";
           socket_.close();
        }
    }

}


void tcp_server::handle_accept(const boost::system::error_code& ec){

    auto newconnection = tcp_socket::create(std::move(listen_sock_));
    connections_.push_back(newconnection);
    auto remote_ep =newconnection->get_sock().remote_endpoint();
    auto remote_ad = remote_ep.address();
    std::string str_addr = remote_ad.to_string();
    LOG(INFO) << str_addr  <<" is accepted ";
    newconnection->start();
    do_accept();
}

void tcp_socket::handle_write( const boost::system::error_code& ec,std::size_t bytes_transferred){

}
