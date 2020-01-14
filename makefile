# Main settings
PROJECT_NAME = elrond
SRC_DIR = src
INCLUDE_DIR = include

# Search for all srcs and includes files
SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name "*.cpp" -or -name "*.c" \) )
INCLUDE_FILES = $(shell find $(INCLUDE_DIR) -type f \( -name "*.hpp" -or -name "*.h" \) )

# Defines src path and source file extensions
VPATH = src: $(SRC_DIR)
vpath %.hpp $(INCLUDE_DIR)
vpath %.h $(INCLUDE_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.c $(SRC_DIR)

.PHONY: all clean test test-all
.DEFAULT_GOAL := all

# *********************************** RULES ************************************
include Linux.mk Arduino.mk

all: $(COMMON_PIC_LIB) $(COMMON_NONPIC_LIB) arduino-dist

clean: clean-build clean-dist

test: $(COMMON_NONPIC_LIB)
	@$(MAKE) --no-print-directory -f test.mk run t="$(t)" l="build/$(COMMON_NONPIC_LIB)" a="$a"

test-all: $(COMMON_NONPIC_LIB)
	@$(MAKE) --no-print-directory -f test.mk all l="build/$(COMMON_NONPIC_LIB)" a="$a"
