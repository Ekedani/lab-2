cmake_minimum_required(VERSION 3.16)
project(lab_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(lab_2
        main.cpp
        "processing_files .cpp"
        "processing_files .h"
)
