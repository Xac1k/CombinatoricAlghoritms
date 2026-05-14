cmake_minimum_required(VERSION 3.10)

project(tests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fconcepts")

find_package(Catch2 3 REQUIRED)
add_executable(tests tests.cpp)

file(GLOB_RECURSE SOURCES utils/*.cpp utils/*.h)

if (SOURCES)
    MESSAGE("Succesfully found")
    #add_library(lib ${SOURCES})
    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain) # lib)
else()
    MESSAGE("folder utils  empty")
endif()