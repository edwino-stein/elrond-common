################################################################################
#                            Tests General settings                            #
################################################################################
set(TEST_CASES_DL dl m)

################################################################################
#                                  Test files                                  #
################################################################################

# Define core files
set(TEST_CATCH_FILE ${PROJECT_SOURCE_DIR}/test/catch.cpp)
set(TEST_EXTERNAL_FILE ${PROJECT_SOURCE_DIR}/test/ExternalMod.cpp)

# Define test cases souce files
file(GLOB_RECURSE SRC_TEST_CASES_FILES "${PROJECT_SOURCE_DIR}/test/*.test.cpp")

################################################################################
#                          External module build rule                          #
################################################################################

# External module test example
add_library(external_module SHARED ${TEST_EXTERNAL_FILE})
set_property(TARGET external_module PROPERTY PREFIX "")
target_compile_options(external_module PRIVATE ${WARNING_LEVEL})

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    # On Linux, the external_module must be linked with PIC common library
    target_link_libraries(
        external_module
        PUBLIC -Wl,--whole-archive ${PROJECT_NAME}.pic -Wl,--no-whole-archive
    )
else()
    # On others platforms, just use the non-PIC common library
    target_link_libraries(external_module ${PROJECT_NAME})
endif()

################################################################################
#                               Test build rules                               #
################################################################################

# Static catch library
add_library(catch OBJECT ${TEST_CATCH_FILE})
target_compile_definitions(catch PRIVATE CATCH_CONFIG_MAIN)

# Test cases definitions
foreach(T ${SRC_TEST_CASES_FILES})
    get_filename_component(TEST_TARGET ${T} NAME_WE)
    add_executable(${TEST_TARGET}.test ${T} $<TARGET_OBJECTS:catch>)
    target_link_libraries(${TEST_TARGET}.test ${PROJECT_NAME}_ext ${TEST_CASES_DL})
    target_compile_options(${TEST_TARGET}.test PRIVATE ${WARNING_LEVEL})
    add_test(${TEST_TARGET}.test ${TEST_TARGET}.test -s)
endforeach()
