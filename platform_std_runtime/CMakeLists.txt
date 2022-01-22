cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    platform_runtime
    DESCRIPTION "Elrond platform runtime library"
    LANGUAGES CXX
)

# Define platform specific dynamic libraries
if(UNIX)
    set(DLINK_LIBS ${CMAKE_DL_LIBS})
endif()

# Find threads library
find_package(Threads REQUIRED)
set(DLINK_LIBS ${DLINK_LIBS} Threads::Threads)

# Define an interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} INTERFACE ${DLINK_LIBS})

# Define an interface library with source files
add_library(${PROJECT_NAME}_src INTERFACE)
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
target_sources(${PROJECT_NAME}_src INTERFACE ${SRC_FILES})
