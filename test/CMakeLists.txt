cmake_minimum_required(VERSION 3.17)

project(
    elrond_tests
    DESCRIPTION "Elrond tests"
    LANGUAGES CXX
)

Include(FetchContent)

# Install Catch2 dependency
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.7)
FetchContent_MakeAvailable(Catch2)

# Build an object with Catch2 entrypoint
add_library(catch2 OBJECT "${PROJECT_SOURCE_DIR}/catch2.cpp")
target_include_directories(catch2 PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(catch2 PRIVATE Catch2::Catch2)

# Search for test cases and exclude catch2 src file
file(GLOB_RECURSE SRC_TEST_CASES_FILES "${PROJECT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM SRC_TEST_CASES_FILES "${PROJECT_SOURCE_DIR}/catch2.cpp")
list(REMOVE_ITEM SRC_TEST_CASES_FILES "${PROJECT_SOURCE_DIR}/dlobject.cpp")

foreach(T ${SRC_TEST_CASES_FILES})

    # Get file name and absolute path
    get_filename_component(TEST_NAME ${T} NAME_WE)
    get_filename_component(FILE_DIR ${T} DIRECTORY)

    # If the path matches with project dir, the test is on root of test
    if(${FILE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
        # Just set the target name with file name
        set(TEST_TARGET ${TEST_NAME})
    else()
        # Remove the absolute path to projeto from directory
        string(REPLACE "${PROJECT_SOURCE_DIR}/" "" FILE_DIR ${FILE_DIR})
        
        # Replace all path bars to underscores
        string(REPLACE "/" ";" TEST_PREFIX ${FILE_DIR})
        list(APPEND TEST_PREFIX ${TEST_NAME})
        string(REPLACE ";" "_" TEST_TARGET "${TEST_PREFIX}")
    endif()

    get_filename_component(FILE_EXT ${T} EXT)
    if(${FILE_EXT} STREQUAL ".test.cpp")
        # If the file name has ".test" extension, is an automated test
        set(TEST_TARGET "${TEST_TARGET}.test")

        # Setup automated tests dependencies
        add_executable(${TEST_TARGET} ${T} $<TARGET_OBJECTS:catch2>)
        target_link_libraries(${TEST_TARGET} PRIVATE Catch2::Catch2)

        # Add to CTEST
        add_test(${TEST_TARGET} ${TEST_TARGET} -s)
    else()
        # else, is just a manual test
        add_executable(${TEST_TARGET} ${T})
    endif()
    
    # Set the incluce directory and add libraries
    target_include_directories(${TEST_TARGET} PRIVATE ${PROJECT_SOURCE_DIR})
    target_link_libraries(${TEST_TARGET} PRIVATE elrond_mock)
        
endforeach()

# Add a DL object for tests
add_library(dlobject SHARED "${PROJECT_SOURCE_DIR}/dlobject.cpp")
set_property(TARGET dlobject PROPERTY PREFIX "")
