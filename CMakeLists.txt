cmake_minimum_required(VERSION 3.9)
project(CPPSandBox)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(TestMain main.cpp basics/stl_move_test.h)