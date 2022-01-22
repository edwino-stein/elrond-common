cmake_minimum_required(VERSION 3.17)
enable_testing()

# Define project info
project(
    elrond
    VERSION 0.5.0
    DESCRIPTION "Elrond Project"
    LANGUAGES CXX
)

# Check the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Define project build stage
set(elrond_DEV_STAGE Alpha)
set(elrond_BUILD_TYPE ${CMAKE_BUILD_TYPE})

# Define C++11 as minimum requirement
set(CMAKE_CXX_STANDARD 11)

# Define warning level
if(MSVC)
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
    endif()
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-Wall -Wextra -pedantic -Werror)
    else()
        add_compile_options(-Wall -Wextra)
    endif()
endif()

# Add subprojects
add_subdirectory(common)
add_subdirectory(platform_std)
add_subdirectory(common_runtime)
add_subdirectory(platform_std_runtime)
add_subdirectory(mock)
add_subdirectory(test)

# Define header only library for common library
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    common
    platform
)

# Export libraries
export(
    TARGETS
        common
        platform
        ${PROJECT_NAME}
    NAMESPACE Elrond::
    FILE elrond.cmake
)
