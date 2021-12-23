cmake_minimum_required(VERSION 3.17)
enable_testing()

project(
    elrond
    VERSION 0.4.0
    DESCRIPTION "Elrond Project"
    LANGUAGES CXX
)

if(NOT DEV_STAGE)
    set(DEV_STAGE Release)
endif()

set(elrond_DEV_STAGE Alpha)
set(elrond_BUILD_TYPE ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Add subprojects
add_subdirectory(common)
add_subdirectory(platform_std)
add_subdirectory(platform_std_runtime)
add_subdirectory(runtime)
add_subdirectory(mock)
add_subdirectory(test)

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
