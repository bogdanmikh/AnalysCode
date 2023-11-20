cmake_minimum_required(VERSION 3.16)
project("ege")

set(CMAKE_CXX_STANDARD 20)

add_executable(ege main.cpp AnalysisCode.cpp AnalysisCode.hpp)