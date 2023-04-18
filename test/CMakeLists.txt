cmake_minimum_required(VERSION 3.17)

project(
    test
    DESCRIPTION "Elrond tests"
    LANGUAGES CXX
)

FILE(GLOB children RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*)
SET(dirlist "")
FOREACH(child ${children})
    IF(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
ENDFOREACH()

SET(SUB_DIRECTORIES "")
SET(SRC_TEST_CASES_FILES "")
FOREACH(dir ${dirlist})
    IF(EXISTS ${PROJECT_SOURCE_DIR}/${dir}/CMakeLists.txt)
        LIST(APPEND SUB_DIRECTORIES ${dir})
    ELSE()
        file(GLOB_RECURSE tcs_files "${PROJECT_SOURCE_DIR}/${dir}/*.cpp")
        LIST(APPEND SRC_TEST_CASES_FILES ${tcs_files})
    ENDIF()
ENDFOREACH()

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
        add_executable(${TEST_TARGET} ${T})
        target_link_libraries(${TEST_TARGET} PRIVATE catch2)

        # Add to CTEST
        add_test(${TEST_TARGET} ${TEST_TARGET} -s)
    else()
        # else, is just a manual test
        add_executable(${TEST_TARGET} ${T})
    endif()
    
    # Set the incluce directory and add libraries
    target_link_libraries(${TEST_TARGET} PRIVATE mock)
        
endforeach()

foreach(S ${SUB_DIRECTORIES})
    add_subdirectory(${S})
endforeach()
