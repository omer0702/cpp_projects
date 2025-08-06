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

class Formatter;
class FormatFactory;

struct LoggerData {
    Level levelType;
    Format formatType;
    int line;
    std::string location;
    std::unique_ptr<Formatter> formatter;

    LoggerData();
};
