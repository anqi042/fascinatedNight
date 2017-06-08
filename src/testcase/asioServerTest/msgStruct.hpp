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
/*-----------head components----------
    uint16_t msg_type_; //2 bytes
    uint16_t msg_body_len_; //2 bytes
    unsigned int msg_peer_id_; //4 bytes
*/
    bool encode(int type,char* buff,uint16_t strlen,unsigned int peer_id){
        if (strlen >= MSGLEN)
            return false;
        switch (type){
            case MSG_TYPE:
                encode_msg_head(std::move(peer_id),std::move(strlen));
                std::memcpy(data+HEADLEN,buff,strlen);
                break;
        }
        return true;
    }
    //assgin action and peer id
    void encode_msg_head(unsigned int && peer_id,uint16_t && strlen){
        //convert to network end
        auto tmp_len = htons(strlen);
        auto tmp_peer = htonl(peer_id);
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
        act = ntohs(act);
        len = ntohs(len);
        peer_id = ntohl(peer_id);
        switch (act){
            case MSG_TYPE:
                return len;
                break;
        }
        return -1;
    }

    char data[TOTALLEN];

    BigDickMsg(){

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
