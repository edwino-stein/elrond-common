cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    runtime
    DESCRIPTION "Elrond runtime libraries"
    LANGUAGES CXX
)

add_subdirectory(common)
add_subdirectory(platform_std)

# Define interface runtime library for headers only
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    runtime_common
    runtime_platform_std
)

# Define interface runtime library for sources only
add_library(${PROJECT_NAME}_src INTERFACE)
target_link_libraries(
    ${PROJECT_NAME}_src
    INTERFACE
    runtime_common_src
    runtime_platform_std_src
)

# Export targets
export(
    TARGETS
        runtime_common
        runtime_common_src
        runtime_platform_std
        runtime_platform_std_src
        runtime
        runtime_src
    NAMESPACE Elrond::
    APPEND FILE ${EXPORT_FILE}
)
