#include<iostream>
#include<fstream>
#include<sstream>
#include "logger.h"
#include "file_channel.h"
#include "socket_channel.h"
#include<thread>
#include<chrono>


#define IP "127.0.0.1"
#define PORT 4321
#define OUTPUTFILE "resLogFile.txt"


void logFromThread(int id){
    for(int i = 0;i <2 ; i++){
        Logger::getInstance().log("Thread"+std::to_string(id)+" - message: "+std::to_string(i), INFO ,TEXT);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void logFromThread2(int id){
    for(int i = 0;i <2 ; i++){
        Logger::getInstance().log("Thread"+std::to_string(id)+" - message: "+std::to_string(i), INFO ,TEXT);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

int main(){
    // //thread safe check file
    // Logger& logger = Logger::getInstance();
    // std::unique_ptr<FileChannel> fileChannel=std::make_unique<FileChannel>("testLog.txt");
    // if(fileChannel->open()){
    //     logger.addChannel(std::move(fileChannel));
    // }

    // int count = 500;
    // std::vector<std::thread> threads;

    // for(int i = 0;i < count; i++){
    //     threads.emplace_back(logFromThread, i);
    // }

    // for(auto& t:threads){
    //     t.join();
    // }

    
    // std::cout<<"logging end, check testLog file"<<std::endl;


    //thread safe check socket
    Logger& logger = Logger::getInstance();

    SocketChannel serverChannel;
    //std::thread serverThread(&SocketChannel::listenerServer, &serverChannel);
    //std::this_thread::sleep_for(std::chrono::milliseconds(200));

    auto clientChannel = std::make_unique<SocketChannel>(IP, PORT);
    if(clientChannel->open()){
        logger.addChannel(std::move(clientChannel));
    }

    int num_of_threads = 1000;
    std::vector<std::thread> threads2;

    for(int i = 0;i < num_of_threads; i++){
        threads2.emplace_back(logFromThread2, i);
    }

    for(auto& t:threads2){
        t.join();
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(500));//giving time to consumer to send all messages
    // logger.closeAllChannels();//close channels, close the client socket, for make the listnerSevrer() to exit from read while
    // serverThread.join();



    //regular check
    // std::string message = "{\"name\":\"omer\",\"age\":[\"years\":\"19\",\"months\":\"4\"]}";
    // SocketChannel obj;
    // std::thread listenerThread(&SocketChannel::listenerServer, &obj);
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));//give server time to complete his connection

    // Logger& logger = Logger::getInstance();


    // std::unique_ptr<FileChannel> fileChannel=std::make_unique<FileChannel>(OUTPUTFILE);
    // if(fileChannel->open()){
    //     logger.addChannel(std::move(fileChannel));
    // }


    // std::unique_ptr<SocketChannel> sockChannel=std::make_unique<SocketChannel>(IP, PORT);
    // if(sockChannel->open()){
    //     logger.addChannel(std::move(sockChannel));
    // }

    // logger.log(message, INFO, JSON);

    // listenerThread.join();//for wait the thread to end

    return 0;
}