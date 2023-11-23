cmake_minimum_required(VERSION 3.26)
project(iscrizioni_gara)

set(CMAKE_CXX_STANDARD 17)

add_executable(iscrizioni_gara main.cpp
        iscrizione.cpp
        iscrizione.h)
