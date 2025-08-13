cmake_minimum_required(VERSION 3.0)

project(logger_run)

set(CMAKE_STANDARD_CXX 17)

include_directories(include)

add_executable(logger_run 
    src/main.cpp
    src/format_classes.cpp
    src/logger.cpp
    src/utils.cpp
    src/logger_data.cpp
    src/file_channel.cpp
    src/socket_channel.cpp
    src/channel.cpp
)