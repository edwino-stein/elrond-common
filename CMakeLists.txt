cmake_minimum_required(VERSION 3.17)
enable_testing()

project(
    elrond
    VERSION 0.4.0
    DESCRIPTION "Elrond Project"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

# Add subprojects
add_subdirectory(common)
add_subdirectory(platform_std)
add_subdirectory(runtime)

#Define header only library
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    elrond_common
)
target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    elrond_platform
)
