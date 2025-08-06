#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#include <string>
#include "format_classes.h"
#include <memory>
#include <fstream>



class Logger {
private:
    int line;
    enum Level levelType;
    enum Format formatType;
    std::string location;
    std::unique_ptr<Formatter> formatter;

    Logger();

    void copyResToLogFile(const std::string& res, Level l);
    //std::string encodeMessage(const std::string& message, Level level);
    //std::string getLevelString(Level level);
    //void handle(const std::string& message, Level level);
    std::string getLogFileName(Level l);

public:
    static Logger& getInstance();

    void setLevel(Level l);
    void setFormat(Format f);
    void setLine(int line);
    void setLocation(const std::string& lo);

    void log(const std::string& message);
};

#endif
