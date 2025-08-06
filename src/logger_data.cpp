#include "logger_data.h"
#include "format_classes.h" 

LoggerData::LoggerData(): levelType(INFO),
      formatType(TEXT), line(-1), location("unknown"), 
      formatter(FormatFactory::createFormatter(TEXT)) {
}
