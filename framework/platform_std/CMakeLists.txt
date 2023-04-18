cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    framework_platform_std
    DESCRIPTION "Elrond standard library specifc code framework library"
    LANGUAGES CXX
)

# Define an interface header only library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")
