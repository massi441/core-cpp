cmake_minimum_required(VERSION 3.21)
project(ml_tests CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../core ${CMAKE_CURRENT_BINARY_DIR}/core)

add_executable(ml_tests ${SOURCES})

target_include_directories(ml_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ml_tests PRIVATE ml_core)
target_link_libraries(ml_tests PRIVATE Catch2::Catch2WithMain)
