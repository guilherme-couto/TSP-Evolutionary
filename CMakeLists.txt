cmake_minimum_required(VERSION 3.10)

SET(CMAKE_CXX_FLAGS "-O3")
SET(CMAKE_C_FLAGS "-O3")

project(TSP-Evolutionary)
file(GLOB source_files
            "*.h"
            "*.hpp"
            "*.cpp"
            "source/*.cpp"
            "include/*.h"
            "include/*.hpp"
    )
add_executable(exec ${source_files})

include_directories(./include)