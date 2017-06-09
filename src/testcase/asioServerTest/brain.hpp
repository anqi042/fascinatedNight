#ifndef BRAIN_HEADER_FILE_H
#define BRAIN_HEADER_FILE_H
#include <memory>
#include <list>
class Connection;
class Server;
class Brain{
    public:

        typedef std::shared_ptr<Connection> ConnPtrType ;
        typedef std::shared_ptr<Server> ServerPtrType ;
        typedef std::shared_ptr<Brain> BrainPtrType ;

    private:
        static std::shared_ptr<Brain> instance;
        Brain(ServerPtrType);
    public:


        static BrainPtrType getInstance(ServerPtrType=nullptr);
        void attach_connec(ConnPtrType);
        void detach_connec(ConnPtrType);

        void monitor_sockets();
    private:
        std::list<ConnPtrType> connList_;

};


#endif
