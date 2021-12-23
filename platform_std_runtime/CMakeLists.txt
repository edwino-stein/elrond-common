cmake_minimum_required(VERSION 3.17)

project(
    elrond_platform_runtime
    DESCRIPTION "Elrond platform runtime library"
    LANGUAGES CXX
)

find_package(Threads REQUIRED)
set(THREAD_LIBRARY Threads::Threads)

set(DLINK_LIBS ${THREAD_LIBRARY})

if(UNIX)
    set(DLINK_LIBS ${DLINK_LIBS} ${CMAKE_DL_LIBS})
endif()

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC elrond ${DLINK_LIBS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ELROND_DISABLE_INLINE)
