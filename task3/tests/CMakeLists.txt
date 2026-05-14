cmake_minimum_required(VERSION 3.10)

project(test)
set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fconcepts")

find_package(Catch2 3 REQUIRED)

add_executable(test tests.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)

