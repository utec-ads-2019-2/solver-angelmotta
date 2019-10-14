cmake_minimum_required(VERSION 3.15)
project(solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(solver main.cpp ConverterToPostfix.h)