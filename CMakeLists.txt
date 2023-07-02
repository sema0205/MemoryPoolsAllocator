cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXE_LINKER_FLAGS "-static")

project(
        lab9
        VERSION 1.0
        DESCRIPTION "C++ Year 2022 Lab9"
        LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(bin)