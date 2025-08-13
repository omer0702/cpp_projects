#pragma once
#include "channel.h"
#include<mutex>
#include<atomic>
#include<queue>
#include<thread>
#include<condition_variable>

class SocketChannel: public Channel{
private:
    std::string host;
    short port;
    int sock_fd;
    std::mutex mtx;

    std::atomic<bool> running{false};
    std::queue<std::string> messagesQueue;
    std::thread consumerThread;
    std::mutex mtxQueue;
    std::condition_variable cv;


    void consumerThreadFunc();

public:
    SocketChannel(const std::string& host, short port);
    SocketChannel();
    ~SocketChannel();

    bool open() override;
    void close() override;
    void write(const std::string& message) override;
    void listenerServer();
};