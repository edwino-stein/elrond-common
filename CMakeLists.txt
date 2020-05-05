cmake_minimum_required(VERSION 3.10)

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

# Includes
include_directories(${PROJECT_SOURCE_DIR}/include)

