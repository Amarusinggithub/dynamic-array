cmake_minimum_required(VERSION 3.24)
project(C_Collections)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_executable(c_collections src/dynarr.c src/llist.c src/main.c src/stack.c src/hashmap.c)
target_include_directories(c_collections PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(c_collections PRIVATE -g -fsanitize=address,undefined)
    target_link_options( c_collections PRIVATE -fsanitize=address,undefined)
    target_compile_definitions (c_collections PRIVATE DEBUG)
endif()

target_compile_options(c_collections PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
