#include "brain.hpp"
#include "msgStruct.hpp"
#include "glog.hpp"
#include <unistd.h>
#include <chrono>
#include <thread>
#include "sockController.hpp"
Brain::Brain(ServerPtrType):connList_(),msg_que_(){
     std::thread(&Brain::monitor_sockets, this).detach();
}

Brain::BrainPtrType Brain::getInstance(Brain::ServerPtrType sPtr){
    if(instance == nullptr){
        instance = BrainPtrType(new Brain(sPtr));
    }else{

    }
    return instance;
}

Brain::BrainPtrType Brain::instance ( nullptr);


void Brain::attach_connec(ConnPtrType cPtr){
    connList_.push_back(cPtr);
    LOG(INFO) <<"connection size: " << connList_.size();
}

void Brain::detach_connec(ConnPtrType cPtr){
    auto itr = connList_.begin();
    for(;itr != connList_.end();++itr){
        if(*itr == cPtr){
            itr = connList_.erase(itr);
            LOG(INFO) <<"connection size: " << connList_.size();
        }
    }
}

void Brain::monitor_sockets(){
    while(1){

        LOG(INFO) << "current connections " << connList_.size() ;
        for(auto itr = connList_.begin();itr != connList_.end();++itr){
            if(!(*itr)->isAlive()){
                itr = connList_.erase(itr);
            }
        }

        std::this_thread::sleep_for (std::chrono::seconds(5));
    }
}

void Brain::msg_enqueue(const BigDickMsg& msg){
    std::lock_guard<std::mutex> lock(mut);
    msg_que_.push(msg);
    cond.notify_one();
}

void Brain::distribute_svc(){
    while(1){
        std::unique_lock<std::mutex> lock(mut);
        while(!(msg_que_.size()  > 0)){
            cond.wait(lock);
        }
        while(msg_que_.size() > 0){
            //transfer
            msg_que_.pop();
        }

    }
}
