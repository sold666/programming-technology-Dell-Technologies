cmake_minimum_required(VERSION 3.19)
project(B5)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "D:\\boost_1_75_0")
set(Boost_USE_STATIC_LIBS ON)

FIND_PACKAGE(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(B5 main.cpp ../common/utility.hpp  ../common/utility.cpp  shape.cpp shape.hpp)

add_executable(test-B5 test-main.cpp test-shape.cpp ../common/utility.hpp  ../common/utility.cpp  shape.cpp shape.hpp)