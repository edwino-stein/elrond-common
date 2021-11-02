cmake_minimum_required(VERSION 3.17)

project(
    elrond_tests
    DESCRIPTION "Elrond tests"
    LANGUAGES CXX
)

Include(FetchContent)

# Install Catch2 dependency
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.1)
FetchContent_MakeAvailable(Catch2)

# Build an object with Catch2 entrypoint
add_library(catch2 OBJECT "${PROJECT_SOURCE_DIR}/catch2.cpp")
target_include_directories(catch2 PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(catch2 PRIVATE Catch2::Catch2)

# Search for test cases
file(GLOB_RECURSE SRC_TEST_CASES_FILES "${PROJECT_SOURCE_DIR}/*.test.cpp")
foreach(T ${SRC_TEST_CASES_FILES})
    get_filename_component(TEST_NAME ${T} NAME_WE)

    get_filename_component(FILE_DIR ${T} DIRECTORY)
    string(REPLACE "${PROJECT_SOURCE_DIR}/" "" FILE_DIR ${FILE_DIR})
    string(REPLACE "/" ";" TEST_PREFIX ${FILE_DIR})
    list(APPEND TEST_PREFIX ${TEST_NAME})

    string(REPLACE ";" "_" TEST_TARGET "${TEST_PREFIX}")
    add_executable(${TEST_TARGET}.test ${T} $<TARGET_OBJECTS:catch2>)
    target_link_libraries(${TEST_TARGET}.test PRIVATE Catch2::Catch2)
    target_include_directories(${TEST_TARGET}.test PRIVATE ${PROJECT_SOURCE_DIR})
    target_link_libraries(${TEST_TARGET}.test PRIVATE elrond)
    add_test(${TEST_TARGET}.test ${TEST_TARGET}.test -s)
endforeach()
