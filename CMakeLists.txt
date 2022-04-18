cmake_minimum_required(VERSION 3.21)
project(cursh C)

set(CMAKE_C_STANDARD 99)
include_directories(/usr/include/readline)

add_executable(cursh main.c)
target_link_libraries(cursh readline)
target_link_libraries(cursh tinfo)

set(CMAKE_C_FLAGS_RELEASE "-Ofast -DNDEBUG -static")