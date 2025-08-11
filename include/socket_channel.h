#pragma once
#include "channel.h"
#include<mutex>


class SocketChannel: public Channel{
private:
    std::string host;
    short port;
    int sock_fd;
    std::mutex mtx;


public:
    SocketChannel(const std::string& host, short port);
    SocketChannel();
    ~SocketChannel();

    bool open() override;
    void close() override;
    bool write(const std::string& message) override;
    void listenerServer();
};