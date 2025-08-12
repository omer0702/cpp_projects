#pragma once
#include "channel.h"
#include<mutex>
#include<fstream>
#include<atomic>
#include<queue>
#include<thread>
#include<condition_variable>

class FileChannel: public Channel{
private:
    std::ofstream resFile;
    std::string fileName;
    std::mutex mtx;

    std::atomic<bool> running{false};//atomic because its a var that use by several threads(consumer/main)
    std::queue<std::string> messagesQueue;
    std::thread consumerThread;
    std::condition_variable cv;

    void consumerThreadFunc();

public:
    FileChannel(const std::string& name);
    ~FileChannel();

    bool open() override;
    void close() override;
    void write(const std::string& message) override;
};