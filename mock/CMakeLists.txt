cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    mock
    DESCRIPTION "Elrond mock utility library for testing"
    LANGUAGES CXX
)

# Look for all source code files
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Define a static library
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "elrond_${PROJECT_NAME}")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC elrond_runtime)
target_link_libraries(${PROJECT_NAME} PRIVATE elrond_runtime_src)
