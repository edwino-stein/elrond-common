cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    framework_common
    DESCRIPTION "Elrond common code framework library"
    LANGUAGES CXX
)

# Create a .in file with version
configure_file(elrond_version.hpp.in elrond_version.hpp)

# Define an interface header only library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_BINARY_DIR}")
