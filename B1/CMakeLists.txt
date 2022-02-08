cmake_minimum_required(VERSION 3.17)
project(B1)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "D:\\boost_1_75_0")
set(Boost_USE_STATIC_LIBS ON)

FIND_PACKAGE(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(B1
        details.hpp tasks.hpp
        tasks.cpp
        policies.hpp main.cpp)
add_executable(test
        details.hpp tasks.hpp
        tasks.cpp
        policies.hpp test-main.cpp test-task1.cpp test-task2.cpp test-task4.cpp test-task3.cpp test-policies.cpp)