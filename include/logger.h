#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#include <string>
#include "format_classes.h"
#include <memory>
#include <fstream>




class Logger {
private:
    LoggerData data;

    Logger();

    void copyResToLogFile(const std::string& res, Level l);
    std::string getLogFileName(Level l);

public:
    static Logger& getInstance();

    void setLevel(Level l);
    void setFormat(Format f);
    void setLine(int line);
    void setLocation(const std::string& lo);
    void setLoggerData(LoggerData ld);

    void log(const std::string& message);
};

#endif
