#include "brain.hpp"
#include "msgStruct.hpp"
#include "glog.hpp"
#include <unistd.h>
#include <chrono>
#include <thread>
#include "sockController.hpp"
Brain::Brain(ServerPtrType):connList_(),msg_que_(){
     std::thread(&Brain::monitor_sockets, this).detach();
     std::thread(&Brain::distribute_svc,this).detach();
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
        LOG(INFO) << "current  online users " << user2connec.size() ;
        for(auto itr = connList_.begin();itr != connList_.end();++itr){
            if(!(*itr)->isAlive()){
                for(auto itr2 = user2connec.begin();itr2 != user2connec.end();++itr2){
                    if(*itr == itr2->second){
                        itr2 = user2connec.erase(itr2);
                        break;
                    }
                }
                itr = connList_.erase(itr);
            }
        }

        std::this_thread::sleep_for (std::chrono::seconds(5));
    }
}

void Brain::set_user2connec(int id,ConnPtrType cPtr){
    user2connec.emplace(id,cPtr);
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
            LOG(INFO) << "wait for msg";
            cond.wait(lock);
        }
        while(msg_que_.size() > 0){
            //transfer
            auto tmp = msg_que_.front();
            LOG(INFO) << "MsgTo user: "<<tmp.msg_peer_id_
                << " " << tmp.data_body();
            auto itr = user2connec.find(tmp.msg_peer_id_);
            if(itr == user2connec.end()){

                LOG(INFO) << "fucked; he is offline";
            }else{
                LOG(INFO) << "send to socket " << tmp.msg_body_len_;
                auto conn = itr->second;
                conn->write_to_myself(tmp.data+BigDickMsg::HEADLEN,
                        tmp.msg_body_len_);
            }
            msg_que_.pop();
        }

    }
}
