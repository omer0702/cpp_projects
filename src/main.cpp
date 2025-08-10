#include<iostream>
#include<fstream>
#include<sstream>
#include "logger.h"
#include "file_channel.h"
#include "socket_channel.h"
#include<thread>


#define IP "127.0.0.1"
#define PORT 4321

int main(){
    std::string message = "{\"name\":\"omer\",\"age\":[\"years\":\"19\",\"months\":\"4\"]}";
    SocketChannel obj;
    std::thread listenerThread(&SocketChannel::listenerServer, &obj);

    Logger& logger = Logger::getInstance();
    // logger.log(message, INFO, JSON);

    //logger.log("miss ;",ERROR, TEXT);


    auto fileChannel=std::make_unique<FileChannel>("resLogFile.txt");
    if(fileChannel->open()){
        logger.addChannel(std::move(fileChannel));
    }


    auto sockChannel=std::make_unique<SocketChannel>(IP, PORT);
    if(sockChannel->open()){
        logger.addChannel(std::move(sockChannel));
    }

    logger.log2(message, INFO, JSON);

    listenerThread.join();

    return 0;
}