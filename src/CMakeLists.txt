cmake_minimum_required(VERSION 3.0)
project(cpp-tetris)

include_directories(include)

add_subdirectory(../tests tests)

file(GLOB sources *.cpp)
list(REMOVE_ITEM sources main.cpp)
add_library(tetris ${sources})
target_compile_options(tetris PUBLIC -std=c++14 -O3 -Wall -Wfloat-conversion)

add_executable(game main.cpp)
target_link_libraries(game tetris)
target_compile_options(game PUBLIC -std=c++14 -O3 -Wall -Wfloat-conversion)