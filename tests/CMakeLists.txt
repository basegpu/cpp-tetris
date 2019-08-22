add_subdirectory(../libs/googletest googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB sources *.cpp)

add_executable(tetris_test ${sources})
target_link_libraries(tetris_test tetrislib gtest)
target_compile_options(tetris_test PUBLIC -std=c++14 -Wall -Wfloat-conversion)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(UnitTests tetris_test)