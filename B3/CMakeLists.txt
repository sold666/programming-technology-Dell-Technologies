cmake_minimum_required(VERSION 3.19)
project(B3)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "D:\\boost_1_75_0")
set(Boost_USE_STATIC_LIBS ON)

FIND_PACKAGE(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(B3
        main.cpp
        factorial-container.hpp factorial-container.cpp tasks.hpp
        phonebook.cpp phonebook.hpp
        phonebook-interface.hpp phonebook-interface.cpp parser.cpp parser.hpp)

add_executable(test-B3
        test-main.cpp tasks.hpp phonebook.cpp phonebook.hpp factorial-container.hpp factorial-container.cpp test-factorial-container.cpp
        phonebook-interface.hpp phonebook-interface.cpp parser.cpp parser.hpp test-parser.cpp
        test-phonebook-interface.cpp test-phonebook.cpp)