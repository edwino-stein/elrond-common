cmake_minimum_required(VERSION 3.17)

project(
    elrond_common
    DESCRIPTION "Elrond common definitions and code"
    LANGUAGES CXX
)

configure_file(elrond_version.hpp.in elrond_version.hpp)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    "${PROJECT_BINARY_DIR}"
)
