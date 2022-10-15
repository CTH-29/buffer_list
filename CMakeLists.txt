cmake_minimum_required(VERSION 2.8)

project(buffer_list C)

add_compile_options(-std=gnu99 -Wall -g)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(./src)

file(GLOB SRC_LISTS src/*.c)

add_executable(test ${SRC_LISTS})
