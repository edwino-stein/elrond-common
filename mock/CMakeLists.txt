cmake_minimum_required(VERSION 3.17)

project(
    elrond_mock
    DESCRIPTION "Elrond mock utility library for testing"
    LANGUAGES CXX
)

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC elrond_runtime)
