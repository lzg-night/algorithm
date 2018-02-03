cmake_minimum_required(VERSION 3.9)
project(list)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES cmake-build-debug/list.h cmake-build-debug/list.c)
add_executable(list ${SOURCE_FILES})