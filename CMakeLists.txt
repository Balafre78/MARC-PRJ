cmake_minimum_required(VERSION 3.27)
project(MARC-PRJ C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(MARC-PRJ main.c
        loc.c
        loc.h
        moves.c
        moves.h
        map.c
        map.h
        queue.c
        queue.h
        stack.c
        stack.h
        tree.c
        tree.h
        utils.c
        utils.h
        testunit.c
        testunit.h)
