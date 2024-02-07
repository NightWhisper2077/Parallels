cmake_minimum_required(VERSION 3.24)
project(Parallel)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(TYPE=float)
add_executable(Parallel main.cpp)
