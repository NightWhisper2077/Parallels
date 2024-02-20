cmake_minimum_required(VERSION 3.24)

add_definitions(-DSIZE=40000)
add_definitions(-DCOUNT=8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

project(Parallels_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Parallels_C main.c)