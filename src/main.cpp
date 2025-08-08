#include<iostream>
#include<fstream>
#include<sstream>
#include "logger.h"




int main(){
    std::string message = "{\"name\":\"omer\",\"age\":[\"years\":\"19\",\"months\":\"4\"]}";


    Logger& logger = Logger::getInstance();
    logger.log(message, INFO, JSON);

    logger.log("miss ;",ERROR, TEXT);
    
    return 0;
}