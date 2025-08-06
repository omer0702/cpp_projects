#include "format_classes.h"
#include<iostream>
#include <sstream>
#include<ctime>
#include<iomanip>
#include "utils.h"




std::string TextFormat::format(const std::string& message, Level l, int line, const std::string& location) {
    std::stringstream encoded;

    if (line >= 0)
    {
        encoded << "[location: " << location << ", line " << line << "]\n";
    }
    encoded << "[" << getTime() << "] ";
    encoded << "[" << getLevel(l) << "] ";

    for (char byte : message)
        encoded << (int)byte << " ";

    return encoded.str();
}

std::string JsonFormat::fixTavs(const std::string& message) {
    std::string res;

    for (char c : message) {
        switch (c) {
            case '\"':
                res += "\\\"";
                break;
            case '\n':
                res += "\\n";
                break;
            case '\t':
                res += "\\t";
                break;
            case '\\':
                res += "\\\\";
                break;

            default:
                res += c;
        }
    }

    return res;
}

std::string JsonFormat::format(const std::string& message, Level l, int line, const std::string& location) {
    std::stringstream encoded;

    if (line >= 0)
    {
        encoded << "[location: " << location << ", line " << line << "]\n";
    }
    encoded << "{\n";
    encoded << "  \"timestamp\": \"" << getTime() << "\",\n";
    encoded << "  \"level\": \"" << getLevel(l) << "\",\n";

    std::string arranged = fixTavs(message);
    std::string nested = Arrange(arranged);
    encoded << "  \"message\": \"" << nested << "\"\n";
    encoded << "}";

    return encoded.str();
}

std::string JsonFormat::Arrange(const std::string& message) {
    std::string res;
    int space = 0;

    for(char c:message){
        if(c=='{'){
            space+=2;
            res+=c;
            res+='\n';
            res.append(c,' ');
        }
        else if(c=='['){
            res+='\n';
            res.append(c,' ');
            space+=2;
            res+=c;
            res+='\n';
            res.append(c,' ');
        }
        else if(c=='}' || c==']'){
            res+='\n';
            space-=2;
            res.append(c,' ');
            res+=c;
        }
        else if(c==','){
            res+=c;
            res+='\n';
            res.append(c,' ');
        }
        else{
            res+=c;
        }

        return res;
    }
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



class JsonWrapper{

};