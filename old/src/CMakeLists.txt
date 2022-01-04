################################################################################
#                                  Functions                                   #
################################################################################

function(get_src_from_header header_file src_dir src_ext out_list)
    file(STRINGS "${header_file}" header_file_content)
    foreach(l ${header_file_content})
        if("${l}" MATCHES "^[ \t]*#[ \t]*include[ \t]*[\"]([^\"]*)[\"]")
            get_filename_component(fp ${CMAKE_MATCH_1} DIRECTORY)
            get_filename_component(fn ${CMAKE_MATCH_1} NAME_WE)
            if(EXISTS "${src_dir}/${fp}/${fn}.${src_ext}")
                list(APPEND rtr "${src_dir}/${fp}/${fn}.${src_ext}")
            endif()
        endif()
    endforeach()
    set(${out_list} ${rtr} PARENT_SCOPE)
endfunction()

################################################################################
#                                Project files                                 #
################################################################################

# Define core files
set(ELROND_COMMON_HPP ${PROJECT_SOURCE_DIR}/include/elrond.hpp)
set(ELROND_EXT_HPP ${PROJECT_SOURCE_DIR}/include/elrond_ext.hpp)
set(ELROND_TEST_HPP ${PROJECT_SOURCE_DIR}/include/elrond_test.hpp)

# Define extented and test source files
get_src_from_header("${ELROND_EXT_HPP}" "${PROJECT_SOURCE_DIR}/src" "cpp" SRC_EXT_FILES)
get_src_from_header("${ELROND_TEST_HPP}" "${PROJECT_SOURCE_DIR}/src" "cpp" SRC_TEST_FILES)

# Define common source files
file(GLOB_RECURSE SRC_COMMON_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SRC_COMMON_FILES ${SRC_EXT_FILES} ${SRC_TEST_FILES})


################################################################################
#                              Dependency settings                             #
################################################################################

find_package(Threads REQUIRED)
set(THREAD_LIBRARY Threads::Threads)

if(UNIX)
    set(EXT_DLINK_LIBS ${CMAKE_DL_LIBS} ${THREAD_LIBRARY})
else()
    set(EXT_DLINK_LIBS ${THREAD_LIBRARY})
endif()

################################################################################
#                            Libraries build rules                             #
################################################################################

# Common static library
add_library(${PROJECT_NAME} STATIC ${SRC_COMMON_FILES})
target_compile_options(${PROJECT_NAME} PRIVATE ${WARNING_LEVEL})

# Extended static library
add_library(${PROJECT_NAME}_ext STATIC ${SRC_EXT_FILES} ${SRC_TEST_FILES})
target_link_libraries(${PROJECT_NAME}_ext PUBLIC ${PROJECT_NAME} ${EXT_DLINK_LIBS})
target_compile_options(${PROJECT_NAME}_ext PRIVATE ${WARNING_LEVEL})

# Linux PIC libraries rules
if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)

    # Common static library with PIC objects
    add_library(${PROJECT_NAME}.pic STATIC ${SRC_COMMON_FILES})
    set_property(TARGET ${PROJECT_NAME}.pic PROPERTY POSITION_INDEPENDENT_CODE ON)
    target_compile_options(${PROJECT_NAME}.pic PRIVATE ${WARNING_LEVEL})

    # Extended static library with PIC objects
    add_library(${PROJECT_NAME}_ext.pic STATIC ${SRC_EXT_FILES})
    set_property(TARGET ${PROJECT_NAME}_ext.pic PROPERTY POSITION_INDEPENDENT_CODE ON)
    target_link_libraries(${PROJECT_NAME}_ext.pic PUBLIC ${PROJECT_NAME}.pic ${EXT_DLINK_LIBS})
    target_compile_options(${PROJECT_NAME}_ext.pic PRIVATE ${WARNING_LEVEL})

endif()
