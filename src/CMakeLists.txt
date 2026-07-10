cmake_minimum_required(VERSION 3.15)
project(core_cpp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # No compiler extensions

add_library(ml_core)

target_include_directories(ml_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

target_sources(ml_core PRIVATE ${SOURCES})
