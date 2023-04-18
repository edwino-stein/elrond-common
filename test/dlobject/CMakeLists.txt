cmake_minimum_required(VERSION 3.17)

project(
    dlobject
    DESCRIPTION "Dynamic load object test"
    LANGUAGES CXX
)

# Add a DL object for tests
add_library(dlobject SHARED "${PROJECT_SOURCE_DIR}/dlobject.cpp")
set_property(TARGET dlobject PROPERTY PREFIX "")
if(MSVC)
    target_compile_definitions(dlobject PUBLIC WINDOWS_DL_API)
endif()

# Add a external module for tests
add_library(ExternalModule SHARED "${PROJECT_SOURCE_DIR}/ExternalModule.cpp")
set_property(TARGET ExternalModule PROPERTY PREFIX "")
target_link_libraries(ExternalModule PUBLIC framework)
target_compile_definitions(ExternalModule PUBLIC ELROND_ENABLE_EXTERNAL_ABI_SETUP)
