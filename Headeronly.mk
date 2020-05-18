# General settings

# Main settings
PROJECT_NAME = elrond
SRC_DIR = src
SRC_TEST_DIR = $(SRC_DIR)/test
INCLUDE_DIR = include
DIST_DIR = dist

# Main headers
ELROND_HPP = include/elrond.hpp
ELROND_EXT_HPP = include/elrond_ext.hpp
ELROND_TEST_HPP = include/elrond_test.hpp

# File extensions
CPP_SRC_EXT = cpp
HPP_SRC_EXT = hpp
IPP_SRC_EXT = ipp

# License text
LICENSE_TXT := head -15 $(ELROND_HPP)

# SED utils
REMOVE_COMMENTS_SCRIPT = tools/remccoms3.sed
REMOVE_COMMENTS := ./$(REMOVE_COMMENTS_SCRIPT) -i
REMOVE_INCLUDES = sed -i '/^\s*\#include\s*\".*\"/d'
REMOVE_EMPTY_LINES = sed -i '/^[[:space:]]*$$/d'

################################### ECL DEFS ###################################

# Define ECL base files names
BASE_HEADER_FILES = $(shell cat $(ELROND_HPP) | grep -Po '\#include\s*"\K[^"]*')

# ECL file options
HEADER_FILES_META = $(addsuffix .$(HPP_SRC_EXT), elrond_version elrond_platform elrond_types)
SRC_FILES_META = $(addsuffix .$(CPP_SRC_EXT), elrond)
SRC_EXCLUDE = interface/% gpio/GpioPin.%

# Define ECL .hpp files
HEADER_FILES := $(HEADER_FILES_META) $(BASE_HEADER_FILES:.$(IPP_SRC_EXT)=.$(HPP_SRC_EXT))
HEADER_FILES := $(addprefix $(INCLUDE_DIR)/, $(HEADER_FILES))

# Define ECL .ipp files
IPP_FILES := $(addprefix $(INCLUDE_DIR)/, $(filter %.$(IPP_SRC_EXT),$(BASE_HEADER_FILES)))

# Define ECL .cpp files
SRC_FILES := $(filter-out $(SRC_EXCLUDE), $(BASE_HEADER_FILES:.$(IPP_SRC_EXT)=.$(HPP_SRC_EXT)))
SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRC_FILES_META) $(SRC_FILES:.$(HPP_SRC_EXT)=.$(CPP_SRC_EXT)))

# Define ECL dist files
HEADERS_DIST = $(subst $(INCLUDE_DIR)/,$(DIST_DIR)/,$(HEADER_FILES))
HEADERS_DIST += $(subst $(INCLUDE_DIR)/,$(DIST_DIR)/,$(addsuffix .$(HPP_SRC_EXT), $(IPP_FILES)))
SRC_DIST = $(subst $(SRC_DIR)/,$(DIST_DIR)/,$(SRC_FILES:.$(CPP_SRC_EXT)=.$(IPP_SRC_EXT)))

################################### EXL DEFS ###################################

# Find EXL base files names
BASE_HEADER_EXT_FILES = $(shell cat $(ELROND_EXT_HPP) | grep -Po '\#include\s*"\K[^"]*')

# EXL file options
HEADER_EXT_FILES_META = $(addsuffix .$(HPP_SRC_EXT), elrond_ext_types elrond_protocol_helper)

# Define EXL files
HEADER_EXT_FILES = $(addprefix $(INCLUDE_DIR)/, $(HEADER_EXT_FILES_META) $(BASE_HEADER_EXT_FILES))

# Define EXL dist files
HEADERS_EXT_DIST = $(subst $(INCLUDE_DIR)/,$(DIST_DIR)/,$(HEADER_EXT_FILES))

################################### ETL DEFS ###################################

# Find ETL base files names
BASE_HEADER_TEST_FILES = $(shell cat $(ELROND_TEST_HPP) | grep -Po '\#include\s*"\K[^"]*')

# ETL file options
HEADER_TEST_FILES_META = $(addsuffix .$(HPP_SRC_EXT), elrond_test_types)

# Define ETL files
HEADER_TEST_FILES = $(addprefix $(INCLUDE_DIR)/, $(HEADER_TEST_FILES_META) $(BASE_HEADER_TEST_FILES:.$(IPP_SRC_EXT)=.$(HPP_SRC_EXT)))

# Define ETL .ipp files
IPP_TEST_FILES := $(addprefix $(INCLUDE_DIR)/, $(filter %.$(IPP_SRC_EXT),$(BASE_HEADER_TEST_FILES)))

# Define ETL dist files
HEADERS_TEST_DIST = $(subst $(INCLUDE_DIR)/,$(DIST_DIR)/,$(HEADER_TEST_FILES) $(addsuffix .$(HPP_SRC_EXT), $(IPP_TEST_FILES)))

################################## UTIL DEFS ###################################

VPATH = src: $(INCLUDE_DIR) $(SRC_DIR)
vpath %.$(HPP_SRC_EXT) $(INCLUDE_DIR)
vpath %.$(IPP_SRC_EXT) $(INCLUDE_DIR)
vpath %.$($(CPP_SRC_EXT)) $(SRC_DIR)

.PHONY: all clean $(PROJECT_NAME).$(HPP_SRC_EXT) $(PROJECT_NAME)_ext.$(HPP_SRC_EXT) $(PROJECT_NAME)_test.$(HPP_SRC_EXT)
.DEFAULT_GOAL := all

################################## BUILD RULES #################################

all: $(PROJECT_NAME).$(HPP_SRC_EXT) $(PROJECT_NAME)_ext.$(HPP_SRC_EXT) $(PROJECT_NAME)_test.$(HPP_SRC_EXT)

# Header only ECL builder
$(PROJECT_NAME).$(HPP_SRC_EXT): $(DIST_DIR)/$(PROJECT_NAME).$(HPP_SRC_EXT)
$(DIST_DIR)/$(PROJECT_NAME).$(HPP_SRC_EXT): $(HEADERS_DIST) $(SRC_DIST)
	@mkdir -p $(@D)
	@eval "$(LICENSE_TXT) > $@"
	@eval "echo '#ifndef _ELROND_HPP\n#define _ELROND_HPP'" >> $@
	@eval "cat $^ >> $@"
	@eval "echo '#endif'" >> $@
	$(info $^ > $@)

# Header only EXL builder
$(PROJECT_NAME)_ext.$(HPP_SRC_EXT): $(DIST_DIR)/$(PROJECT_NAME)_ext.$(HPP_SRC_EXT)
$(DIST_DIR)/$(PROJECT_NAME)_ext.$(HPP_SRC_EXT): $(HEADERS_EXT_DIST) $(DIST_DIR)/$(PROJECT_NAME)_test.$(HPP_SRC_EXT)
	@mkdir -p $(@D)
	@eval "$(LICENSE_TXT) > $@"
	@eval "echo '#ifndef _ELROND_EXTENDED_HPP\n#define _ELROND_EXTENDED_HPP'" >> $@
	@eval "echo '#include <elrond.hpp>'" >> $@
	@eval "cat $^ >> $@"
	@eval "echo '#endif'" >> $@
	$(info $^ > $@)

# Header only ETL builder
$(PROJECT_NAME)_test.$(HPP_SRC_EXT): $(DIST_DIR)/$(PROJECT_NAME)_test.$(HPP_SRC_EXT)
$(DIST_DIR)/$(PROJECT_NAME)_test.$(HPP_SRC_EXT): $(HEADERS_TEST_DIST)
	@mkdir -p $(@D)
	@eval "echo '#ifndef _ELROND_TEST_HPP\n#define _ELROND_TEST_HPP'" >> $@
	@eval "cat $^ >> $@"
	@eval "echo '#endif'" >> $@
	$(info $^ > $@)

# Specific platform.hpp parser
$(DIST_DIR)/elrond_platform.$(HPP_SRC_EXT): $(INCLUDE_DIR)/elrond_platform.$(HPP_SRC_EXT)
	@mkdir -p $(@D)
	@cp $< $@
	eval "sed -i 's/^\s*\/\/\s*#define\s*ELROND_WITH_INLINE_FUNC/    #define ELROND_WITH_INLINE_FUNC/g' $@"
	@eval "$(REMOVE_INCLUDES) $@ && $(REMOVE_COMMENTS) $@ && $(REMOVE_EMPTY_LINES) $@"
	$(info $< > $@)

# Generic .hpp parser
$(DIST_DIR)/%.$(HPP_SRC_EXT): $(INCLUDE_DIR)/%.$(HPP_SRC_EXT)
	@mkdir -p $(@D)
	@cp $< $@
	@eval "$(REMOVE_INCLUDES) $@ && $(REMOVE_COMMENTS) $@ && $(REMOVE_EMPTY_LINES) $@"
	$(info $< > $@)

# Generic .ipp parser
$(DIST_DIR)/%.$(IPP_SRC_EXT).$(HPP_SRC_EXT): $(INCLUDE_DIR)/%.$(IPP_SRC_EXT)
	@mkdir -p $(@D)
	@cp $< $@
	@eval "$(REMOVE_INCLUDES) $@ && $(REMOVE_COMMENTS) $@ && $(REMOVE_EMPTY_LINES) $@"
	$(info $< > $@)

# Generic .cpp to .ipp parser
$(DIST_DIR)/%.$(IPP_SRC_EXT): $(SRC_DIR)/%.$(CPP_SRC_EXT)
	@mkdir -p $(@D)
	@cp $< $@
	@eval "$(REMOVE_INCLUDES) $@ && $(REMOVE_COMMENTS) $@ && $(REMOVE_EMPTY_LINES) $@"
	$(info $< > $@)

clean:
	rm -rf $(DIST_DIR)
