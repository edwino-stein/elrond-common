cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    runtime_platform_std
    DESCRIPTION "Elrond standard library runtime library"
    LANGUAGES CXX
)

# Define platform specific dynamic libraries
if(UNIX)
    set(DLINK_LIBS ${CMAKE_DL_LIBS})
endif()

# Look for all source code files
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Define an interface library for headers only
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} INTERFACE framework_platform_std)

# Define an interface library for sources only
add_library(${PROJECT_NAME}_src INTERFACE)
target_sources(${PROJECT_NAME}_src INTERFACE ${SRC_FILES})
