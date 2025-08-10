#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#include <string>
#include "format_classes.h"
#include <memory>
#include <fstream>
#include<vector>
#include "channel.h"


class Logger {
private:
    std::unique_ptr<Formatter> formatter;
    std::vector<std::unique_ptr<Channel>> channels;

    Logger();

    //void copyResToLogFile(const std::string& res, Level l);

public:
    static Logger& getInstance();

    void log(const std::string& message, Level l, Format f);
    void log2(const std::string& message, Level l, Format f);

    void addChannel(std::unique_ptr<Channel> channel);

};

#endif
