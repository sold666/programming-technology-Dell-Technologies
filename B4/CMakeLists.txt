cmake_minimum_required(VERSION 3.19)
project(B4)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "D:\\boost_1_75_0")
set(Boost_USE_STATIC_LIBS ON)

FIND_PACKAGE(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(B4 main.cpp data-structure.cpp data-structure.hpp ../common/utility.hpp  ../common/utility.cpp)

add_executable(test-B4 test-main.cpp test-data-structure.cpp data-structure.cpp data-structure.hpp)