#pragma once
#include "channel.h"
#include<mutex>
#include<fstream>


class FileChannel: public Channel{
private:
    std::ofstream resFile;
    std::string fileName;
    std::mutex mtx;

public:
    FileChannel(const std::string& name);
    ~FileChannel();

    bool open() override;
    void close() override;
    bool write(const std::string& message) override;
};