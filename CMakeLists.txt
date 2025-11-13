cmake_minimum_required(VERSION 3.10)
project(MyProgram LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

add_executable(p01 p01.cpp)
add_executable(p02 p02.cpp)
add_executable(p03 p03.cpp)