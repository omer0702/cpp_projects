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

#define FILENAME "logger.c"


Logger::Logger(){
    
}

Logger& Logger::getInstance(){//singleton
    static Logger instance;
    return instance;
}

void Logger::setLevel(Level l){
    data.levelType=l;
}

void Logger::setLine(int l){
    data.line=l;
}

void Logger::setLocation(const std::string& lo){
    data.location=lo;
}

void Logger::setFormat(Format f){
    data.formatType=f;
    data.formatter=FormatFactory::createFormatter(f);
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

void Logger::log(const std::string& message){
    std::string encoded = data.formatter->format(message, data);
    copyResToLogFile(encoded, data.levelType);
}



int main(){
    std::ifstream testFile("test.txt");//read mode
    std::stringstream buff;
    std::string content;

    if(testFile.is_open()){//copy textfile content to a var
        buff << testFile.rdbuf();
        testFile.close();
    }
    else{
        std::cout<< "failed to open test file" <<std::endl;
    }

    content = buff.str();


    std::string nestedJson = "{\"name\":\"omer\",\"age\":[\"years\":\"19\",\"months\":\"4\"]}";//for handle nested json input

    // Singleton::getInstance(nestedJson, INFO, JSON, 1, FILENAME);//create the first instance
    // //Singleton::getInstance(content, INFO, JSON, 1);

    // Singleton::getInstance("x = 10", DEBUG, TEXT, 2, FILENAME);//update the instance
    // Singleton::getInstance("miss ;", ERROR, TEXT, 3, FILENAME);


    Logger& log = Logger::getInstance();
    log.setFormat(JSON);
    log.setLevel(WARN);
    log.setLine(2);
    log.setLocation(FILENAME);
    log.log(nestedJson);

    log.setFormat(TEXT);
    log.setLevel(DEBUG);
    log.setLine(21);
    log.setLocation(FILENAME);
    log.log("x=10");




    // regular use
    // logger log1(content, INFO, TEXT);
    // logger log2(content, WARN, JSON);

    // logger log3("update success",INFO, TEXT);
    // logger log4("danger to overflow",WARN, TEXT);
    // logger log5("miss ;",ERROR, TEXT);
    // logger log6("x = 10",DEBUG, TEXT);


    // //use with prototype design pattern->that means to clone objects with small chang,its instead of create new object
    // //use unique ptr for auto delte
    // std::unique_ptr<logger> base = std::make_unique<logger>(content, INFO, JSON);

    // std::unique_ptr<logger> warn(base->clone());
    // warn->setLevel(WARN);
    // warn->startLog();

    // std::unique_ptr<logger> error(base->clone());
    // error->setLevel(ERROR);
    // error->startLog();

    return 0;
}