cmake_minimum_required(VERSION 3.10)

project(main)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fconcepts")

find_package(Catch2 3 REQUIRED)
add_executable(main main.cpp)

file(GLOB_RECURSE SOURCES utils/*.cpp utils/*.h)


if (SOURCES)
    add_library(lib ${SOURCES})
    set(SFML_DIR "/home/xac1k/SFML-3.0.2/lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)
    target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-audio sfml-system GL lib)
else()
    MESSAGE("folder utils  empty")
endif()