cmake_minimum_required(VERSION 3.17)

project(
    catch2
    DESCRIPTION "Catch2 unit test library"
    LANGUAGES CXX
)

Include(FetchContent)

# Install Catch2 dependency
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.7)
FetchContent_MakeAvailable(Catch2)

# Build a library with Catch2 entrypoint
add_library(catch2 STATIC "${PROJECT_SOURCE_DIR}/catch2.cpp")
target_include_directories(catch2 PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(catch2 PUBLIC Catch2::Catch2)

# Export targets
export(
    TARGETS Catch2 catch2
    NAMESPACE Elrond::
    APPEND FILE ${EXPORT_FILE}
)
