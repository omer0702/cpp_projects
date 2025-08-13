#pragma once

#include <string>
#include <memory>

enum Level {
    INFO = 0,
    WARN = 1,
    ERROR = 2,
    DEBUG = 3
};

enum Format {
    TEXT = 0,
    JSON = 1
};



struct LoggerData {
    Level levelType;
    Format formatType;
    int line;
    std::string location;

    LoggerData()=delete;

    LoggerData(Level level, Format format);
};
