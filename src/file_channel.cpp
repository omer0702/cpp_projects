#include "file_channel.h"
#include<iostream>
#include<chrono>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<cstring>


FileChannel::FileChannel(const std::string& name):fileName(name){

}

FileChannel::~FileChannel(){
    close();
}

void FileChannel::consumerThreadFunc(){
    while(running){
        std::unique_lock<std::mutex> lock(mtx);

        while(messagesQueue.empty() && running){
            cv.wait(lock);
        }

        while(!messagesQueue.empty()){
            std::string msg=messagesQueue.front();
            messagesQueue.pop();

            if(resFile.is_open()){
                resFile<<msg<<"\n";
            }
        }
    }
}


bool FileChannel::open(){
    std::lock_guard<std::mutex> lock(mtx);

    resFile.open(fileName, std::ios::app);
    if(!resFile.is_open()){
        return false;
    }
    running=true;
    consumerThread=std::thread(&FileChannel::consumerThreadFunc, this);

    return true;
}

void FileChannel::close(){
    running=false;

    cv.notify_all();
    if(consumerThread.joinable()){
        consumerThread.join();
    }
    
    std::lock_guard<std::mutex> lock(mtx);

    if(resFile.is_open()){
        resFile.close();
    }
}


void FileChannel::write(const std::string& res){
    std::lock_guard<std::mutex> lock(mtx);
    messagesQueue.push(res);
    cv.notify_one();
}