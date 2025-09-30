cmake_minimum_required(VERSION 3.22)
project(SortingAlgorithmsVisualization C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SortingAlgorithmsVisualization
        main.c
        app.c
#        app.h
        compare.c
#        compare.h
        inputs.c
#        inputs.h
        logger.c
#        logger.h
#        settings.h
        sorting.c
#        sorting.h
        stats.c
#        stats.h
        thread.c
#        thread.h
        utils.c
#        utils.h
        visual.c
#        visual.h
        )

target_link_libraries(SortingAlgorithmsVisualization PRIVATE SDL2 SDL2_ttf SDL2_gfx)
