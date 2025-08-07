#include<iostream>
#include<fstream>
#include<sstream>
#include "logger.h"


#define FILENAME "logger.cpp"

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
    LoggerData jsonData, textData;

    jsonData.levelType=INFO;
    jsonData.formatType=JSON;
    jsonData.line=1;
    jsonData.location=FILENAME;
    log.log(nestedJson, jsonData);

    textData.levelType=ERROR;
    textData.formatType=TEXT;
    textData.line=11;
    textData.location=FILENAME;
    log.log("miss ;", textData);

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