cmake_minimum_required(VERSION 3.10)

project(graph)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fconcepts")

#file(GLOB_RECURSE SOURCES lib/*.cpp lib/*.h lib/*.hpp)
add_library(libs INTERFACE)
target_include_directories(libs INTERFACE /lib) 

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE libs)