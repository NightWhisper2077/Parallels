cmake_minimum_required(VERSION 3.24)
project(Parallel)

option(double "set_double" OFF)
set(CMAKE_CXX_STANDARD 17)

if(double)
    add_compile_definitions(TYPE=double)
else()
    add_compile_definitions(TYPE=float)
endif()

add_executable(Parallel main.cpp)
