find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(ml_tests ${SOURCES})

target_include_directories(ml_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ml_tests PRIVATE ml_core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(ml_tests)
