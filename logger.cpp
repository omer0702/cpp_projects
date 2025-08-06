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






// class Formatter{//interface
//     public:
//     virtual std::string format(const std::string& message, Level l, int line, std::string lo)=0;//pure virtual, means that the subclasses must implement

//     virtual ~Formatter(){};//for properly deleting of derived object, both destructors are called
// };

// class TextFormat:public Formatter{
//     private:
//     std::stringstream encoded;

//     public:
//     std::string format(const std::string& message, Level l, int line, std::string lo) override{
//         //std::stringstream encoded;

//         if(line >= 0){
//             encoded << "[location: "<<lo<<", line "<<line<<"] "<<"\n";
//         }
//         encoded << "[" <<getTime()<< "] ";
//         encoded << "[" <<getLevel(l)<<"] ";
        
//         //int i = 0;
//         for(char byte: message){
//             encoded << (int)byte <<" ";
//             //std::cout<<"byte number "<<i<<": "<<byte<<std::endl;            
//         }

//         return encoded.str();
//     }
// };

// class JsonFormat:public Formatter{
//     private:
//     //var for json nesting
//     //json jsonOutput;
//     std::stringstream encoded;

//     std::string fixTavs(const std::string& message){
//         std::string tavs;

//         for(char c: message){
//             if(c=='"'){
//                 tavs+="\"";
//             }
//             else if(c=='\n'){
//                 tavs+="\\n";
//             }
//             else if(c=='\t'){
//                 tavs+="\\t";
//             }
//             else if(c=='{'){
//                 tavs+="\\{";
//             }
//             else if(c=='}'){
//                 tavs+="\\}";
//             }
//             else{
//                 tavs+=c;
//             }
//         }

//         return tavs;
//     }

//     std::string fixTavs2(const std::string& message){
//         std::string tavs;
//         int countOpen=0;
//         int countClose=0;


//         for(char c: message){
//             if(c=='\"'){
//                 tavs+="\\\"";
//             }
//             if(c=='\\'){
//                 tavs+="\\\\";
//             }
//             else if(c=='\n'){
//                 tavs+="\\n";
//             }
//             else if(c=='\t'){
//                 tavs+="\\t";
//             }
//             else if(c=='{'){
//                 countOpen++;
//                 tavs+="{";
//             }
//             // else if(c=='{' && countOpen>1){
//             //     tavs+='\n';
//             // }
//             else if(c=='}'){
//                 countClose++;
//                 tavs+="\\}";
//             }
//             // else if(c=='}' && countClose>1){
//             //     tavs+='\n';
//             // }
//             else{
//                 tavs+=c;
//             }
//         }

//         return tavs;
//     }

//     public:
//     std::string format(const std::string& message, Level l, int line, std::string lo) override{
//         //std::stringstream encoded;

        
//         if(line >= 0){
//             encoded << "[location: "<<lo<<", line "<<line<<"] "<<"\n";
//         }
//         encoded <<"{\n";
//         encoded <<" \"timestamp\": \""<<getTime()<< "\",\n";//there is \ in the code for create a "" in part of string
//         encoded <<" \"level\": \"" <<getLevel(l)<< "\",\n";
//         encoded <<" \"message\": \"" <<fixTavs2(message)<< "\"\n";
//         encoded <<"}";

//         return encoded.str();
//     }

//     // std::string format2(const std::string& message, Level l, int line, std::string lo) {
//     //     jsonOutput["timestamp"] = getTime();
//     //     jsonOutput["level"] = getLevel(l);
//     //     jsonOutput["message"] = nlohmann::json::parse(message);//try to save it in json format
//     //     //handle a case he doesnt success^

//     //     std::stringstream s;
//     //     if(line >= 0){
//     //         s<<"[line: "<<line<<"]\n";
//     //     }

//     //     s<<jsonOutput.dump(3);//3 spaces
//     //     return s.str();
//     // }
// };

// class FormatFactory{
//     public:
//     static std::unique_ptr<Formatter> createFormatter(Format f){//static because he can be two types
//         if(f == TEXT){
//             return std::make_unique<TextFormat>();
//         }
//         else if(f == JSON){
//             return std::make_unique<JsonFormat>();
//         }
//         else{
//             std::cout<<"invalid foramt"<<std::endl;
//         }

//         //return nullptr;
//     }
// };



// class logger{
//     private:
//     //LoggerData data;
//     enum Level levelType;
//     std::string msg;
//     std::string res;
//     std::string logFileName = "resfile.txt";
//     enum Format format;

//     int line;//line number that the log detected
//     std::string location;


//     std::string getLogFileName(Level l){
//         return "log_"+getLevel(l)+".txt";
//     }

//     void copyResToLogFile(std::string& res,Level l) {
//         //std::string logFileName=getLogFileName(l);
//         //log files by level
//         std::ofstream logFile(getLogFileName(l), std::ios::app);//app is append mode(from the end of the file)

//         if(logFile.is_open()){
//             logFile << res << std::endl;
//             logFile.close();
//         }
//         else{
//             std::cout<< "failed to open log file" <<std::endl;
//         }

//         //log file that contains all the log msg, not by level
//         std::ofstream totalLogFile(logFileName, std::ios::app);
//         if(totalLogFile.is_open()){
//             totalLogFile<<res<<std::endl;
//             totalLogFile.close();
//         }
//         else{
//             std::cout<<"failed to open total log file"<< std::endl;
//         }

//         std::cout<<"["<<getLevel(l)<<"]"<<getLogFileName(l)<<":"<<std::endl;
//         std::cout<<res<<std::endl<< std::endl;
//     }

//     // std::string encodeText(const std::string& message, Level l){
//     //     std::stringstream encoded;
//     //     encoded << "[" <<getTime()<< "] ";
//     //     encoded << "[" <<getLevel(l)<<"] ";

//     //     int i = 0;
//     //     for(char byte: message){
//     //         encoded << (int)byte <<" ";
//     //         //std::cout<<"byte number "<<i<<": "<<byte<<std::endl;            
//     //     }

//     //     return encoded.str();
//     // }

//     // std::string encodeJson(const std::string& message, Level l){
//     //     std::stringstream encoded;

//     //     encoded <<"{\n";
//     //     encoded <<" \"timestamp\": \""<<getTime()<< "\",\n";//there is \ in the code for create a "" in part of string
//     //     encoded <<" \"level\": \"" <<getLevel(l)<< "\",\n";
//     //     encoded <<" \"message\": \"" <<fixTavs(message)<< "\"\n";
//     //     encoded <<"}";

//     //     return encoded.str();
//     // }

//     // std::string fixTavs(const std::string& message){
//     //     std::string tavs;

//     //     for(char c: message){
//     //         if(c=='"'){
//     //             tavs+="\"";
//     //         }
//     //         else if(c=='\n'){
//     //             tavs+="\\n";
//     //         }
//     //         else if(c=='\t'){
//     //             tavs+="\\t";
//     //         }
//     //         else{
//     //             tavs+=c;
//     //         }
//     //     }

//     //     return tavs;
//     // }


        
//     // void handle(const std::string& message, Level l, Format f){
//     //     if(f == TEXT){
//     //         res=encodeText(message, l);
//     //     }
//     //     else if(f == JSON){
//     //         res=encodeJson(message, l);
//     //     }
//     //     else{
//     //         std::cout<<"invalid fotamt"<<std::endl;
//     //     }

//     //     copyResToLogFile(res, l);
//     // }

//     void handle2(const std::string& message, Level l, Format f, int line, std::string lo){
//         auto formatter=FormatFactory::createFormatter(f);//auto because i dont know which type will be
//         res=formatter->format(message,l, line, lo);

//         copyResToLogFile(res, l);
//     }

//     void showLine(){//show the line that the log was detected
//         //add line variable
//         std::cout<<"log in line: "<<line<<std::endl;
//     }


//     public:

//     logger(const std::string& message, Level l, Format f, int lineNumber):msg(message), levelType(l), format(f), line(lineNumber){
//         handle2(msg, levelType, f, lineNumber, location);
//     }


//     ~logger(){

//     }

//     //there is no need in my copy ctor because i want to copy all object vars
//     // logger(const logger& new_l){//copy ctor
//     //     this->levelType=new_l.levelType;
//     //     this->msg=new_l.msg;
//     //     this->format=new_l.format;
//     //     this->logFileName=new_l.logFileName;
//     // }

//     void setLevel(Level l){
//         levelType=l;
//     }

//     void setMessage(std::string message){
//         msg=message;
//     }

//     void setLine(int ln){
//         line=ln;
//     }

//     void setFormat(Format f){
//         format=f;
//     }
    
//     void setLocation(std::string lo){
//         location=lo;
//     }


//     //for prototype design pattern
//     logger* clone(){
//         return new logger(*this);//calling copy ctor
//     }

//     void startLog(){
//         handle2(msg, levelType, format, line, location);
//     }
// };




// class Singleton{
//     private:
//     static std::unique_ptr<logger> l_instance;

//     Singleton();//private ctor, for no create instances
    
//     public:
//     static logger* getInstance(const std::string& message, Level l, Format f, int line, std::string lo){
//         if(!l_instance){
//             l_instance = std::make_unique<logger>(message, l, f, line);
//         }
//         else{//maybe change to one fun that update all vars
//             l_instance->setMessage(message);
//             l_instance->setLevel(l);
//             l_instance->setLine(line);
//             l_instance->setFormat(f);
//             l_instance->setLocation(lo);
//             l_instance->startLog();
//         }

//         return l_instance.get();
//     }
// };
// std::unique_ptr<logger> Singleton::l_instance=nullptr;


Logger::Logger(){
    levelType=INFO;
    line=-1;
    formatType=TEXT;
    location="unknown";
    formatter=FormatFactory::createFormatter(TEXT);
}

Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}

void Logger::setLevel(Level l){
    levelType=l;
}

void Logger::setLine(int l){
    line=l;
}

void Logger::setLocation(const std::string& lo){
    location=lo;
}

void Logger::setFormat(Format f){
    formatType=f;
    formatter=FormatFactory::createFormatter(f);
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
    std::string encoded = formatter->format(message, levelType, line, location);
    copyResToLogFile(encoded, levelType);
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