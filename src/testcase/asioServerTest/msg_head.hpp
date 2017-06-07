#ifndef MSG_HEADER_FILE_H
#define MSG_HEADER_FILE_H
// your code
#include<cstring>
#include <string>
#include <cstdio>

class BigDickMsg{
    public:
        BigDickMsg():LOGIN("FUCK"),MESSAGE("YOU"),QUIT("ASSHOLE"){

        }
        enum { MAX_MSG_LEN = 512,
               HEADKEYLEN = 10,
               HEADLENLEN = 4,
               TOTALMSGLEN = MAX_MSG_LEN+HEADKEYLEN+HEADLENLEN
        };

        const std::string LOGIN;
        const std::string MESSAGE;
        const std::string QUIT;

        void encodeMsg(std::string peer,char * buffer, int len){
            int tab = HEADKEYLEN - MESSAGE.size();
            std::string s = std::to_string(tab);
            std::string format = "%" + s + "d";
            std::sprintf(buffer,format.c_str(),MESSAGE.c_str());
        }

        char * data(){
            return data_;
        }

    private:
        char data_[HEADLENLEN + HEADKEYLEN + MAX_MSG_LEN];

};



#endif
