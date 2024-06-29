cmake_minimum_required(VERSION 3.27)
project(code C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

add_executable(code
        io.c
        headers/io.h
        print.c)

add_executable(execute
        execute.c
        io.c
        headers/io.h)

add_executable(generate
        generate.c
        io.c
        headers/io.h)
