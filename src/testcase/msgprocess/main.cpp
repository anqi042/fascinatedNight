// your code
#include<cstring>
#include <string>
#include <cstdio>
#include <iostream>

class BigDickMsg{
    public:
        BigDickMsg():LOGIN("FUCK"),MESSAGE("YOU"),QUIT("ASSHOLE"),data_("\0"){

        }
        enum { MAX_MSG_LEN = 512,
               HEADKEYLEN = 10,
               HEADLENLEN = 4,
               HEADPEERLEN= 10,
               TOTALMSGLEN = MAX_MSG_LEN+HEADKEYLEN+HEADLENLEN,

               TYPE_MSG = 1,
               TYPE_LOGIN = 2,
               TYPE_QUIT = 3
        };

        const std::string LOGIN;
        const std::string MESSAGE;
        const std::string QUIT;

        void encodeMsg(std::string peer,char * buffer, int len, int type=TYPE_MSG){
            switch(type){
                case TYPE_MSG:
                    int tab = HEADKEYLEN - MESSAGE.size();
                    std::string s = std::to_string(tab);
                    std::string format = "%" + s + "s";
                    std::sprintf(data_,format.c_str(),MESSAGE.c_str());
                    break;
                case TYPE_QUIT:
                    break;
                case TYPE_LOGIN:
                    break;

            }
        }

        char * data(){
            return data_;
        }

        void debug_show(){
            std::cout << data_ << std::endl;
        }

    private:
        char data_[HEADLENLEN + HEADKEYLEN + MAX_MSG_LEN];

};

int main(){
    BigDickMsg msg;
    char a[] = "bigdick";
    msg.encodeMsg("",a,std::strlen(a));
    msg.debug_show();

}


