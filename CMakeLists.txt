cmake_minimum_required(VERSION 3.14)
project(Short C)

option(DEBUG "Enable debug sanitizer mode" OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SRC_FILES src/*.c)

add_executable(Short ${SRC_FILES})
target_compile_options(Short PRIVATE -Wall -Wextra)