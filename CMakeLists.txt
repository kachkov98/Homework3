cmake_minimum_required(VERSION 2.6)
project(homework3)

SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

add_library(vector STATIC vector.cpp)
add_library(matrix STATIC matrix.cpp)
link_libraries(matrix vector)

add_executable(level1 level1.cpp)
target_link_libraries(level1 matrix)
