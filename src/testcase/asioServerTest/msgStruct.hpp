#ifndef MSG_HEADER_FILE_H
#define MSG_HEADER_FILE_H
#include <cstring>
#include <cstdint>
#include <iostream>
#include <utility>
#include <arpa/inet.h>
class BigDickMsg{
    public:
    enum {
        HEADLEN=8,
        MSGLEN=512,
        TOTALLEN=520,

        LOGIN_TYPE=1,
        MSG_TYPE=2,
        QUIT_TYPE=3,

        U16LEN = sizeof(uint16_t),
        U32LEN = sizeof(unsigned int)

    };
    uint16_t msg_type_; //2 bytes
    uint16_t msg_body_len_; //2 bytes
    unsigned int msg_peer_id_; //4 bytes

    bool encode_msg_buff_only(char* buff,int strlen){
        msg_body_len_ = strlen;
        if (strlen >= MSGLEN)
            return false;
        encode_msg_head();
        std::memcpy(data+HEADLEN,buff,strlen);
        return true;
    }


    bool encode(int type,char* buff,uint16_t strlen,unsigned int peer_id){
        msg_type_ = type;
        msg_body_len_=strlen;
        msg_peer_id_ = peer_id;
        if (strlen >= MSGLEN)
            return false;
        switch (type){
            case MSG_TYPE:
                encode_msg_head();
                std::memcpy(data+HEADLEN,buff,strlen);
                break;
        }
        return true;
    }

    //assgin action and peer id
    void encode_msg_head(){
        //convert to network end
        auto tmp_len = htons(msg_body_len_);
        auto tmp_peer = htonl(msg_peer_id_);
        uint16_t t = htons(MSG_TYPE);
        std::memcpy(data,(char*)&t,U16LEN);
        std::memcpy(data+U16LEN,(char*)&tmp_peer,U32LEN);
        std::memcpy(data+U16LEN+U32LEN,(char*)&tmp_len, U16LEN);
    }

/*--------------decode---------------------------------*/
    //return message length or -1 if failed
    int decode_head(char *headbuff){
        uint16_t act;
        uint16_t len;
        unsigned int peer_id;
        std::memcpy((char*)&act,headbuff,U16LEN);
        std::memcpy((char*)&peer_id,headbuff+U16LEN,U32LEN);
        std::memcpy((char*)&len,headbuff+U16LEN+U32LEN,U16LEN);
        msg_type_ = ntohs(act);
        msg_body_len_ = ntohs(len);
        msg_peer_id_ = ntohl(peer_id);
        std::cout << msg_type_ << " " << msg_body_len_ << " " << msg_peer_id_<< std::endl;
        switch (msg_type_){
            case MSG_TYPE:
                return len;
                break;
        }
        return -1;
    }

    char data[TOTALLEN];

    BigDickMsg():data("\0"){

    }
    ~BigDickMsg(){
    }
};
/*
int _test_123123123(){
    BigDickMsg msg;
    //std::cout << sizeof(msg) << std::endl;
    char buffer[]="hello world";
uint16_t i = std::strlen(buffer);
std::cout << i << std::endl;
    //encode a message
    msg.encode(BigDickMsg::MSG_TYPE,buffer,std::strlen(buffer),6677);
    auto l = msg.decode_head(msg.data);
    std::cout << l << std::endl;
    return 0;
}
*/
#endif
