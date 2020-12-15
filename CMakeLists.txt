cmake_minimum_required(VERSION 3.15)
project(ECE209Prog3 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -pedantic")

add_executable(ECE209Prog3 main.c phones.c)