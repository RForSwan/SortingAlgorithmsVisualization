cmake_minimum_required(VERSION 4.0)
project(SortingAlgorithmsVisualization C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SortingAlgorithmsVisualization
        main.c
        settings.h
        sorting.c
        sorting.h
        stats.c
        stats.h
        utils.c
        utils.h
        visual.c
        visual.h
        visual.c
        main.c)

target_link_libraries(SortingAlgorithmsVisualization PRIVATE SDL2 SDL2_ttf SDL2_gfx)
