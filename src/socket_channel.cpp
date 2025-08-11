#include "socket_channel.h"
#include<iostream>
#include<chrono>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<cstring>
#include<cerrno>

#define SIZE 1024


SocketChannel::SocketChannel(const std::string& h, short p):host(h), port(p), sock_fd(-1){

}

SocketChannel::SocketChannel(){

}

SocketChannel::~SocketChannel(){
    close();
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

    return true;
}


void SocketChannel::close(){
    std::lock_guard<std::mutex> lock(mtx);//lock_guard is a wrapper class to mutex
    if(sock_fd != -1){
        ::close(sock_fd);//the :: means to call global close()
    }
}

bool SocketChannel::write(const std::string& res){
    int bytes_send;
    std::lock_guard<std::mutex> lock(mtx);

    if(sock_fd == -1){
        return false;
    }
    bytes_send=send(sock_fd, res.c_str(), res.size(), 0);//c_str() convert to char*

    return bytes_send==res.size();//return if all bytes sent
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

    while((bytes_read=read(client_fd, buff, SIZE-1)) > 0){
        buff[bytes_read]='\0';
        std::cout<<"received: \n"<<buff<<std::endl;
    }

    ::close(server_fd);
    ::close(client_fd);
}