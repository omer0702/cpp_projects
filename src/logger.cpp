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



Logger::Logger(){
    
}

Logger& Logger::getInstance(){//singleton
    static Logger instance;
    return instance;
}



std::string Logger::getLogFileName(Level l){
    return "log_"+getLevel(l)+".txt";
}

void Logger::copyResToLogFile(const std::string& res, Level l){
    std::ofstream logFile(getLogFileName(l), std::ios::app);//app is append mode(from the end of the file)

    if(logFile.is_open()){
        logFile << res << std::endl;
        logFile.close();
    }
    else{
        std::cout<< "failed to open log file" <<std::endl;
    }

    //log file that contains all the log msg, not by level
    std::ofstream totalLogFile("resFile.txt", std::ios::app);
    if(totalLogFile.is_open()){
        totalLogFile<<res<<std::endl;
        totalLogFile.close();
    }
    else{
        std::cout<<"failed to open total log file"<< std::endl;
    }

    std::cout<<"["<<getLevel(l)<<"]"<<getLogFileName(l)<<":"<<std::endl;
    std::cout<<res<<std::endl<< std::endl;
}

void Logger::log(const std::string& message, const LoggerData& data){
    std::unique_ptr<Formatter> formatter = FormatFactory::createFormatter(data.formatType);
    std::string encoded = formatter->format(message, data);
    copyResToLogFile(encoded, data.levelType);
}



