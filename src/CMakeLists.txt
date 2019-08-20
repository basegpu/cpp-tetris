cmake_minimum_required(VERSION 3.0)
project(cpp-tetris)

file(GLOB_RECURSE sources *.cpp *.hpp)

add_executable(tetris ${sources})

target_compile_options(tetris PUBLIC -std=c++14 -O3 -Wall -Wfloat-conversion)