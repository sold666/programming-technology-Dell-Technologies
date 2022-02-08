cmake_minimum_required(VERSION 3.16)
project(A3)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "D:\\boost_1_75_0")
set(Boost_USE_STATIC_LIBS ON)

FIND_PACKAGE(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(A3
        main.cpp
        base-types.hpp circle.cpp
        circle.hpp rectangle.cpp
        rectangle.hpp shape.hpp
        composite-shape.hpp composite-shape.cpp)