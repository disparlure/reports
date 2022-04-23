cmake_minimum_required(VERSION 3.12)

project(trafficreport)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")
add_library(trafficreport ${SOURCES})

target_include_directories(trafficreport PUBLIC include)
target_include_directories(trafficreport PUBLIC data)

add_subdirectory(test)
#add_subdirectory(visualization)
#add_executable(TrafficReport main.cpp trafficreport.cpp)
