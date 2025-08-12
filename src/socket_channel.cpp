#include "socket_channel.h"
#include<iostream>
#include<chrono>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<cstring>
#include<cerrno>

#define SIZE 1024

#define ENDTAV "\nEND\n"

SocketChannel::SocketChannel(const std::string &h, short p) : host(h), port(p), sock_fd(-1){
}

SocketChannel::SocketChannel(){
}

SocketChannel::~SocketChannel(){
    close();
}


void SocketChannel::consumerThreadFunc(){
    long bytes_send;

    while(true){
        std::unique_lock<std::mutex> lock(mtxQueue);//to prevent from two threads to change the queue in the same time
        while(messagesQueue.empty() && running){//consumer wait when the queue is empty, and awake when there the producer add msg
            cv.wait(lock);//for not waste cpu time
        }

        if(!running || messagesQueue.empty()){
            break;
        }
        
        std::string msg=std::move(messagesQueue.front());
        messagesQueue.pop();
        lock.unlock();//after we have the msg, unlock the queue for not block producers

        std::lock_guard<std::mutex> sockLock(mtx);//lock the socket in sned time to prevent parallel sending
        if(sock_fd!=-1){
            if((bytes_send=send(sock_fd, msg.c_str(), msg.size(), 0)) < 0){
                std::cerr<<"send failed: "<<strerror(errno)<<std::endl;
            }
        }
    }
}

bool SocketChannel::open(){
    sockaddr_in server_addr{};

    sock_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd<0){
        std::cout<<"socket creation failed"<<std::endl;
        return false;
    }

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(host.c_str());

    if(connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        std::cerr<<"connect failed:"<<strerror(errno)<<std::endl;
        std::cout<<"socket connection failed"<<std::endl;
        return false;
    }

    running=true;
    consumerThread=std::thread(&SocketChannel::consumerThreadFunc, this);//thread that takes messages from the queue and send to the socket

    return true;
}


void SocketChannel::close(){
    running=false;//stop the consumer
    cv.notify_all();//awake the consumer if he waits in empty condition

    std::unique_lock<std::mutex> lock(mtx);
    if(sock_fd != -1){
        ::close(sock_fd);
        sock_fd= -1;
    }
    lock.unlock();//unlock before join, because the consumer thread can be blocked in send() and the join will still wait for him

    if(consumerThread.joinable()){//make sure that the consumer thread end before we continue
        consumerThread.join();
    }
}

void SocketChannel::write(const std::string& res){//the producer
    if(!running){
        return;
    }

    std::lock_guard<std::mutex> lock(mtxQueue);
    messagesQueue.push(res+ENDTAV);
    cv.notify_one();//awake the consumer thread if he sleeps and wait to new messages
}



void SocketChannel::listenerServer(){
    int server_fd=socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    char buff[SIZE];
    int bytes_read, client_fd;

    address.sin_family=AF_INET;
    address.sin_port=htons(4321);
    address.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0){
        std::cout<<"bind failed"<<std::endl;
        return;
    }
    if(listen(server_fd, 3)<0){
        std::cout<<"listen failed"<<std::endl;
        return;  
    }
    
    std::cout<<"listening on port: 4321"<<std::endl;
    if((client_fd=accept(server_fd, nullptr, nullptr)) < 0){
        std::cout<<"accept failed"<<std::endl;
        std::cerr<<"accept failed:"<<strerror(errno)<<std::endl;
    }

    std::string buffer;
    while((bytes_read=read(client_fd, buff, SIZE-1)) > 0){
        buff[bytes_read]='\0';
        buffer+=buff;

        long pos;
        while((pos=buffer.find(ENDTAV))!=std::string::npos){//for print the whole message
            std::string message=buffer.substr(0,pos);
            buffer.erase(0, pos+strlen(ENDTAV));
            std::cout<<"received: \n"<<message<<std::endl;
        }
    }

    ::close(server_fd);
    ::close(client_fd);
}
