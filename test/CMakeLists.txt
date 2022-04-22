cmake_minimum_required(VERSION 3.10)

project(TrafficReportTest)

link_libraries(trafficreport)

add_executable(TrafficReportTest main.cpp)

enable_testing()

add_test(NAME test_basic_parse COMMAND TrafficReportTest)
