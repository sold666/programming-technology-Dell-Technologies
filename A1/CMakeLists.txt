cmake_minimum_required(VERSION 3.17)
project(A1)

set(CMAKE_CXX_STANDARD 14)

add_executable(A1
        base-types.hpp
        circle.cpp
        circle.hpp
        main.cpp
        rectangle.cpp
        rectangle.hpp)
