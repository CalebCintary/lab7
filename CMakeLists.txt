cmake_minimum_required(VERSION 3.17)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c MatrixType.h TV.h)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(untitled ${CURSES_LIBRARIES})