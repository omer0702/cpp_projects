#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "logger.h"
#include<memory>
#include<ctime>
#include<iomanip>
#include "utils.h"
#include <sys/socket.h>


using namespace std;


Logger::Logger(){
    
}

Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}



void Logger::addChannel(std::unique_ptr<Channel> ch){
    channels.push_back(std::move(ch));
}


void Logger::log(const std::string& message, Level l, Format f){
    formatter = FormatFactory::createFormatter(f);
    std::string encoded = formatter->format(message, LoggerData(l, f));
    
    for(auto &ch:channels){
        ch->write(encoded);
    }
}
