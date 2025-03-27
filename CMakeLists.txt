cmake_minimum_required(VERSION 3.30)
project(tree)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)

add_executable(tree src/main.cpp
        src/tree_maker.cpp)

enable_testing()