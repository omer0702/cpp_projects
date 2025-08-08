#include "logger_data.h"
#include "format_classes.h" 

#define FILENAME "logger.cpp"
#define LINENUMBER 10


LoggerData::LoggerData(): levelType(INFO),
      formatType(TEXT), line(-1), location("unknown"){

}

LoggerData::LoggerData(Level level, Format format){
      levelType=level;
      formatType=format;
      line=LINENUMBER;
      location=FILENAME;
}