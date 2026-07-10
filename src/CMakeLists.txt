add_library(ml_core)

target_include_directories(ml_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

target_sources(ml_core PRIVATE ${SOURCES})
