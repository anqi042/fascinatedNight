#ifndef BRAIN_HEADER_FILE_H
#define BRAIN_HEADER_FILE_H
#include <queue>
#include <memory>
#include <list>
#include <condition_variable>
#include <mutex>
#include <unordered_map>
class Connection;
class Server;
class BigDickMsg;
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
        //manage connections
        void attach_connec(ConnPtrType);
        void detach_connec(ConnPtrType);
        void monitor_sockets();
        void set_user2connec(int id,ConnPtrType cPtr);

        //msg queue operation
        void msg_enqueue(const BigDickMsg& msg);
        void distribute_svc();
    private:
        std::list<ConnPtrType> connList_;
        std::queue<BigDickMsg> msg_que_;

        //queue locks
        std::condition_variable cond;
        std::mutex mut;

        std::unordered_map<int,ConnPtrType> user2connec;
};


#endif
