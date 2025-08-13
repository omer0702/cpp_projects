#include "format_classes.h"
#include<iostream>
#include <sstream>
#include<ctime>
#include<iomanip>
#include "utils.h"


std::string TextFormat::format(const std::string& message, LoggerData ldata) {
    std::stringstream encoded;

    if (ldata.line >= 0){
        encoded << "[location: " << ldata.location << ", line " << ldata.line << "]\n";
    }
    encoded << "[" << getTime() << "] ";
    encoded << "[" << getLevel(ldata.levelType) << "] ";

    for (char byte : message){
        encoded << (int)byte << " ";
    }

    return encoded.str();
}


std::string JsonFormat::format(const std::string& message, LoggerData ldata) {
    std::stringstream encoded;

    if (ldata.line >= 0)
    {
        encoded << "[location: " << ldata.location << ", line " << ldata.line << "]\n";
    }
    encoded << "{\n";
    encoded << "  \"timestamp\": \"" << getTime() << "\",\n";
    encoded << "  \"level\": \"" << getLevel(ldata.levelType) << "\",\n";

    //std::string arranged = fixTavs(message);
    std::string nested = Arrange(message);
    encoded << "  \"message\": \"" << nested << "\"\n";
    encoded << "}";

    return encoded.str();
}

std::string JsonFormat::Arrange(const std::string& message) {
    std::string res;
    int space = 0;

    for(char c:message){
        if(c=='{'){
            space+=4;
            res+=c;
            res+='\n';
            res.append(space,' ');
        }
        else if(c=='['){
            res+='\n';
            res.append(space,' ');
            space+=4;
            res+=c;
            res+='\n';
            res.append(space,' ');
        }
        else if(c=='}' || c==']'){
            res+='\n';
            space-=4;
            res.append(space,' ');
            res+=c;
        }
        else if(c==','){
            res+=c;
            res+='\n';
            res.append(space,' ');
        }
        else{
            res+=c;
        }
    }

    return res;
}


std::unique_ptr<Formatter> FormatFactory::createFormatter(Format f) {
    if (f==TEXT){
        return std::make_unique<TextFormat>();
    }
    else if (f==JSON){
        return std::make_unique<JsonFormat>();
    }
    
    return std::make_unique<TextFormat>();
}