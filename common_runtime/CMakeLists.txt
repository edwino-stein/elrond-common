cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    common_runtime
    DESCRIPTION "Elrond common runtime library"
    LANGUAGES CXX
)

# Define an interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_compile_definitions(${PROJECT_NAME} INTERFACE ELROND_DISABLE_INLINE)

# Define an interface library with source files
add_library(${PROJECT_NAME}_src INTERFACE)
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
target_sources(${PROJECT_NAME}_src INTERFACE ${SRC_FILES})
