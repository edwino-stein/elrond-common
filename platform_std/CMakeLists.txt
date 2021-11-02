cmake_minimum_required(VERSION 3.17)

project(
    elrond_platform
    DESCRIPTION "Elrond platform specific definitions and code"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    "${PROJECT_SOURCE_DIR}/include"
)
