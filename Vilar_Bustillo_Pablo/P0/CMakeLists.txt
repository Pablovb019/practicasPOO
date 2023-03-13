cmake_minimum_required(VERSION 3.24)
project(P0)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(P0
        cadena.cpp
        cadena.hpp
        fecha.cpp
        fecha.hpp)
