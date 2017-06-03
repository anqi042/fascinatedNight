#include "mySocket.hpp"

void tcp_socket::handle_read(const boost::system::error_code& ec,
        std::size_t bytes_transferred){
    if(!ec){

        std::cout << bytes_transferred << std::endl;
    }else if(ec.value() == boost::system::errc::errc_t::operation_canceled){
        //if error is operation cancelled,socket has been closed ;
        //this occurs when using netcat or unfriendly client
        std::cout << ec.value() << " " << ec.message() <<std::endl;
    }

}
