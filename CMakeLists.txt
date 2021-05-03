cmake_minimum_required(VERSION 3.17)
project(extmem_c C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(extmem_c
        extmem.c
        extmem.h
        myextmem.c q1.c q1.h q2.c q2.h)
