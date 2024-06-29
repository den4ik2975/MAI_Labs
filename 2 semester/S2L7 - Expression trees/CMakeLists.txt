cmake_minimum_required(VERSION 3.27)
project(untitled3 C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled3 main.c
        stack.c
        headers/stack.h
        headers/utils.h
        utils.c
        headers/postfix.h
        postfix.c
        tree.c
        headers/tree.h
        exp_stack.c
        headers/exp_stack.h
)
