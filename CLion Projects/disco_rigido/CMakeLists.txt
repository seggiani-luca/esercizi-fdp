cmake_minimum_required(VERSION 3.26)
project(disco_rigido)

set(CMAKE_CXX_STANDARD 17)

add_executable(disco_rigido main.cpp
        disco.cpp
        disco.h)
