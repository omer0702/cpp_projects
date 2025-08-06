#include<string>
#pragma once


enum Level{
    INFO = 0,
    WARN = 1,
    ERROR = 2,
    DEBUG = 3
};

enum Format{
    TEXT = 0,
    JSON = 1
};

std::string getTime();
std::string getLevel(Level l);