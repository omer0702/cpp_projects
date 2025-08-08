#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#include <string>
#include "format_classes.h"
#include <memory>
#include <fstream>


class Logger {
private:
    std::unique_ptr<Formatter> formatter;

    Logger();

    void copyResToLogFile(const std::string& res, Level l);

public:
    static Logger& getInstance();

    void log(const std::string& message, Level l, Format f);
};

#endif
