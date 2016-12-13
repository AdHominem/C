cmake_minimum_required(VERSION 3.5)
project(c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")

set(SOURCE_FILES main.c crypto.h)
add_executable(c ${SOURCE_FILES})
target_link_libraries(c m)