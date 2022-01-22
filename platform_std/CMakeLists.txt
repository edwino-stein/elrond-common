cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    platform
    DESCRIPTION "Elrond platform specific definitions and code"
    LANGUAGES CXX
)

# Define an interface header only library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories( ${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")
