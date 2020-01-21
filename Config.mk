################################################################################
#                            General build settings                            #
################################################################################

# Main settings
PROJECT_NAME = elrond
SRC_DIR = src
SRC_TEST_DIR = $(SRC_DIR)/test
INCLUDE_DIR = include
BUILD_DIR = build

# Util
TEST_MAKEFILE = Test.mk
COMMON_NAME_LIB = lib$(PROJECT_NAME)
TEST_NAME_LIB = lib$(PROJECT_NAME)-test
INCLUDES = $(INCLUDE_DIR)
MACROS =

# File extensions
CPP_SRC_EXT = cpp
C_SRC_EXT = c
OBJ_EXT = o
DEP_EXT = d
DYNAMIC_LIB_EXT = so
STATIC_LIB_EXT = a

TARGET_OS = $(shell uname -s)
ifeq ($(TARGET_OS), Linux)
    # Linux compiler and linker settings
    CXX = g++
    CXXFLAGS = -std=c++11 -Wall -MMD -c
    LDFLAGS = -std=c++11 -Wall
    LDLIBS =
    AR = ar
    ARFLAGS = rs
endif
