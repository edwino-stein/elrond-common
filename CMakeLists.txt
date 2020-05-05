cmake_minimum_required(VERSION 3.10)
enable_testing()

################################################################################
#                           Project General settings                           #
################################################################################

set(PROJECT_NAME elrond)
project(
    ${PROJECT_NAME}
    VERSION 0.4.0
    DESCRIPTION "Elrond Common Library"
    LANGUAGES CXX
)

# Enable C++11 standard
set(CMAKE_CXX_STANDARD 11)

# Define warning level
if(MSVC)
    set(WARNING_LEVEL /W3 /WX)
else()
    # TODO: add -pedantic flag?
    set(WARNING_LEVEL -Wall)
endif()

# Includes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Define main source directory
add_subdirectory(src)

# Define tests source directory
add_subdirectory(test)
