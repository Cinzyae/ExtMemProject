cmake_minimum_required(VERSION 3.17)
project(extmem_c C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(extmem_c
        extmem.c
        extmem.h
        myextmem.c)
