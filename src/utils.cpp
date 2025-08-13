#include "utils.h"
#include<ctime>
#include<sstream>
#include<iostream>
#include<iomanip>


std::string getTime(){
    std::ostringstream time;
    std::time_t seconds=std::time(nullptr);//curr time in seconds
    std::tm* localTime=std::localtime(&seconds);//convert to normal time

    time<<std::put_time(localTime, "%d/%m/%Y %H:%M:%S");
    return time.str();
}

std::string getLevel(Level l){
    switch (l)
    {
        case INFO:
            return "INFO";
        
        case WARN:
            return "WARN";

        case ERROR:
            return "ERROR";

        case DEBUG:
            return "DEBUG";
            
        default:
            std::cout<<"in default"<<std::endl;
            return "unknown";
    }
}