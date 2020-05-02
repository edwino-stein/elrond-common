################################################################################
#                            General build settings                            #
################################################################################

# Main settings
PROJECT_NAME = elrond
SRC_DIR = src
SRC_TEST_DIR = $(SRC_DIR)/test
INCLUDE_DIR = include
BUILD_DIR = build
DIST_DIR = dist
TEST_DIR = test

# Library names
COMMON_NAME_LIB = lib$(PROJECT_NAME)
EXT_NAME_LIB = lib$(PROJECT_NAME)_ext

# Main headers
ELROND_HPP = include/elrond.hpp
ELROND_EXT_HPP = include/elrond_ext.hpp
ELROND_TEST_HPP = include/elrond_test.hpp

# Util
TEST_MAKEFILE = Test.mk
HO_MAKEFILE = Headeronly.mk
INCLUDES = $(INCLUDE_DIR)
MACROS =

# File extensions
CPP_SRC_EXT = cpp
C_SRC_EXT = c
HPP_SRC_EXT = hpp
IPP_SRC_EXT = ipp
OBJ_EXT = o
DEP_EXT = d
DYNAMIC_LIB_EXT = so
STATIC_LIB_EXT = a

# Source files
SRC_FILES =
SRC_EXT_FILES =
SRC_TEST_FILES =

TARGET_OS = $(shell uname -s)
ifeq ($(TARGET_OS), Linux)

    # Linux compiler and linker settings
    CXX = g++
    CXXFLAGS = -std=c++11 -Wall -MMD -c
    LDFLAGS = -std=c++11 -Wall
    LDLIBS =
    AR = ar
    ARFLAGS = rs

	# Find files from include/elrond_ext.hpp of Elrond Extended Library
    SRC_EXT_FILES = $(shell cat $(ELROND_EXT_HPP) | grep -Po '\#include\s*"\K[^"]*')
    SRC_EXT_FILES := $(addprefix $(SRC_DIR)/, $(SRC_EXT_FILES:.$(HPP_SRC_EXT)=.$(CPP_SRC_EXT)))

    # Find files of Elrond Test Library
    SRC_TEST_FILES = $(shell find $(SRC_TEST_DIR) -type f \( -name "*.$(CPP_SRC_EXT)" -or -name "*.$(C_SRC_EXT)" \) )

    # Find files of Elrond Common Library
    SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name "*.$(CPP_SRC_EXT)" -or -name "*.$(C_SRC_EXT)" \) )
    SRC_FILES := $(filter-out $(SRC_EXT_FILES) $(SRC_TEST_FILES), $(SRC_FILES))

	# Elrond libraries setup
    COMMON_STATIC_LIB = $(BUILD_DIR)/$(COMMON_NAME_LIB).$(STATIC_LIB_EXT)
    EXT_STATIC_LIB = $(BUILD_DIR)/$(EXT_NAME_LIB).$(STATIC_LIB_EXT)

	# Find files of all test cases
    ALL_TEST_SRC = $(shell find $(TEST_DIR) -type f \( -name "*.test.cpp" \))

endif
