cmake_minimum_required(VERSION 3.20)
project(2021)

set(CMAKE_CXX_STANDARD 20)

add_executable(2021 main.cpp Day1.cpp Day2.cpp Day2.h)


add_custom_command(TARGET 2021 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Input
        ${CMAKE_CURRENT_BINARY_DIR}/Input)
