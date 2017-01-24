cmake_minimum_required(VERSION 2.6)
project(romannum)

add_executable(romannum main.cpp)

install(TARGETS romannum RUNTIME DESTINATION bin)
