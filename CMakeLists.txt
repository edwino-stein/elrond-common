cmake_minimum_required(VERSION 3.10)
enable_testing()

################################################################################
#                 Load version from include/elrond_version.hpp                 #
################################################################################

file(READ "include/elrond_version.hpp" ELROND_VERSION)
string(REGEX MATCHALL "ELROND_API_(MAJOR|MINOR|PATCH)[ \t]*([0-9]*)" ELROND_VERSION ${ELROND_VERSION})
foreach(v ${ELROND_VERSION})
    string(REGEX MATCH "[0-9]+" vn ${v})
    string(REGEX MATCH "(MAJOR|MINOR|PATCH)" v ${v})
    set(ELROND_${v} ${vn})
endforeach()
set(ELROND_VERSION ${ELROND_MAJOR}.${ELROND_MINOR}.${ELROND_PATCH})

################################################################################
#                           Project General settings                           #
################################################################################

project(
    elrond
    VERSION ${ELROND_VERSION}
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
