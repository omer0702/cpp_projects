#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "logger.h"
#include<memory>
#include<ctime>
#include<iomanip>
#include "utils.h"

using namespace std;

#define OUTPUTFILE "resFile.txt"

Logger::Logger(){
    
}

Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}




void Logger::copyResToLogFile(const std::string& res, Level l){
    std::ofstream totalLogFile(OUTPUTFILE, std::ios::app);
    if(totalLogFile.is_open()){
        totalLogFile<<res<<std::endl;
        totalLogFile.close();
    }
    else{
        std::cout<<"failed to open total log file"<< std::endl;
    }

    std::cout<<"["<<getLevel(l)<<"]"<<OUTPUTFILE<<":"<<std::endl;
    std::cout<<res<<std::endl<< std::endl;
}

void Logger::log(const std::string& message, Level l, Format f){
    formatter = FormatFactory::createFormatter(f);
    std::string encoded = formatter->format(message, LoggerData(l, f));
    copyResToLogFile(encoded, l);
}



