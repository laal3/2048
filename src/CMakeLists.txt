cmake_minimum_required(VERSION 3.7)

project(2048)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(2048 main.c)
target_link_libraries(2048 ${SDL2_LIBRARIES})