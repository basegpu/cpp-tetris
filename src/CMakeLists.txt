cmake_minimum_required(VERSION 3.0)
project(cpp-tetris)

add_executable(tetris main.cpp)

target_compile_options(tetris PUBLIC -std=c++14 -O3 -Wall -Wfloat-conversion)

add_subdirectory(../libs/googletest googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tetris_test tests.cpp)

target_link_libraries(tetris_test gtest)
target_compile_options(tetris_test PUBLIC -std=c++14 -Wall -Wfloat-conversion)