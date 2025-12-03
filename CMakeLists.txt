cmake_minimum_required(VERSION 3.10)
project(MyProgram LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

add_executable(webMain webMain.cpp)
