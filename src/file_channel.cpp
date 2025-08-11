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

bool FileChannel::open(){
    std::lock_guard<std::mutex> lock(mtx);
    resFile.open(fileName, std::ios::app);
    return resFile.is_open();
}

void FileChannel::close(){
    std::lock_guard<std::mutex> lock(mtx);

    if(resFile.is_open()){
        resFile.close();
    }
}


bool FileChannel::write(const std::string& res){
    std::lock_guard<std::mutex> lock(mtx);
    if(!resFile.is_open()){
        std::cout<<"res file is closed, cant write"<<std::endl;
        return false;
    }
    resFile<<res<<std::endl;

    return true;
}