cmake_minimum_required(VERSION 3.27)
project(Practice9 C)

set(CMAKE_C_STANDARD 23)

add_executable(Practice9 main.c
        table_shit/table.h
        key_functions/keys.h
        key_functions/keys.c
        table_shit/table.c
        lab_staff/utils.h
        lab_staff/utils.c)
