cmake_minimum_required(VERSION 2.8.12.2)
project(project2)

set(CMAKE_CXX_STANDARD 11)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



set(SOURCE_FILES main.cpp Customer.cpp Customer.h Cashier.cpp Cashier.h Barista.cpp Barista.h)
add_executable(project2 ${SOURCE_FILES})
