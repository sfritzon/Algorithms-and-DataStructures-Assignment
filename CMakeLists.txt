cmake_minimum_required(VERSION 3.16)
project(SortingVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        6.0
)
FetchContent_MakeAvailable(raylib)
message(STATUS "raylib_SOURCE_DIR = ${raylib_SOURCE_DIR}")

add_executable(Algorithms-and-DataStructures-Assignment
    src/main.cpp
)

target_include_directories(Algorithms-and-DataStructures-Assignment PRIVATE
    src
    src/include
    ${raylib_SOURCE_DIR}/src
)

target_link_libraries(Algorithms-and-DataStructures-Assignment PRIVATE raylib)
