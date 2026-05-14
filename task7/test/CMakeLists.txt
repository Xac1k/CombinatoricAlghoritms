cmake_minimum_required(VERSION 3.10)

project(main)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fconcepts")

add_executable(main main.cpp)

file(GLOB_RECURSE SOURCES utils/*.cpp utils/*.h utils/*.hpp)


if (SOURCES)
    add_library(lib ${SOURCES})
    target_link_libraries(main PRIVATE lib )
else()
    MESSAGE("folder utils  empty")
endif()