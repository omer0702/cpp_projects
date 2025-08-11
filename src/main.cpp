#include<iostream>
#include<fstream>
#include<sstream>
#include "logger.h"
#include "file_channel.h"
#include "socket_channel.h"
#include<thread>


#define IP "127.0.0.1"
#define PORT 4321
#define OUTPUTFILE "resLogFile.txt"

int main(){
    std::string message = "{\"name\":\"omer\",\"age\":[\"years\":\"19\",\"months\":\"4\"]}";
    SocketChannel obj;
    std::thread listenerThread(&SocketChannel::listenerServer, &obj);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));//give server time to complete his connection

    Logger& logger = Logger::getInstance();


    std::unique_ptr<FileChannel> fileChannel=std::make_unique<FileChannel>(OUTPUTFILE);
    if(fileChannel->open()){
        logger.addChannel(std::move(fileChannel));
    }


    std::unique_ptr<SocketChannel> sockChannel=std::make_unique<SocketChannel>(IP, PORT);
    if(sockChannel->open()){
        logger.addChannel(std::move(sockChannel));
    }

    logger.log(message, INFO, JSON);

    listenerThread.join();//for wait the thread to end

    return 0;
}