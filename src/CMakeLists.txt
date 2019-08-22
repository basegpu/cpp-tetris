cmake_minimum_required(VERSION 3.0)
project(cpp-tetris)

include_directories(include)

add_subdirectory(../tests tests)

add_executable(tetris main.cpp)
target_compile_options(tetris PUBLIC -std=c++14 -O3 -Wall -Wfloat-conversion)