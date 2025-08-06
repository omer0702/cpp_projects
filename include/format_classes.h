#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "utils.h"



class Formatter {
public:
    virtual std::string format(const std::string& message, const LoggerData& ldata)=0;
    virtual ~Formatter() {}
};


class TextFormat : public Formatter {
public:
    std::string format(const std::string& message, const LoggerData& ldata) override;
};

class JsonFormat : public Formatter {
public:
    std::string format(const std::string& message,const LoggerData& ldata) override;

private:
    std::string fixTavs(const std::string& message);
    std::string Arrange(const std::string& message);
};


class FormatFactory {
public:
    static std::unique_ptr<Formatter> createFormatter(Format f);
};
