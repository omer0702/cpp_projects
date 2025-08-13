#include "logger_data.h"
#include "format_classes.h" 



LoggerData::LoggerData(Level level, Format format){
      levelType=level;
      formatType=format;
      line=__LINE__;
      location=__FILE__;
}