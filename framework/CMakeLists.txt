cmake_minimum_required(VERSION 3.17)

# Define project info
project(
    framework
    DESCRIPTION "Elrond framework libraries"
    LANGUAGES CXX
)

add_subdirectory(common)
add_subdirectory(platform_std)

# Define header only library for common library
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    framework_common
    framework_platform_std
)

# Export targets
export(
    TARGETS framework_common framework_platform_std framework
    NAMESPACE Elrond::
    FILE ${EXPORT_FILE}
)