cmake_minimum_required(VERSION 4.0)
project(untitled7 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled7
        main.c
        utils.c
        structure.c
        hasse.c
        tarjan.c)

target_include_directories(untitled7 PRIVATE .)

