# General settings
include Config.mk

HEADER_FILES = $(addsuffix .$(HPP_SRC_EXT), $(addprefix $(INCLUDE_DIR)/, version platform types))\
			   $(shell find $(INCLUDE_DIR)/runtime -type f -name "*.$(HPP_SRC_EXT)")\
			   $(shell find $(INCLUDE_DIR)/interface -type f -name "*.$(HPP_SRC_EXT)")\
			   $(addsuffix .$(HPP_SRC_EXT), $(addprefix $(INCLUDE_DIR)/module/, BaseModule\
			   BaseGpioModule BaseInputDriverModule BaseTransportModule))\
			   $(shell find $(INCLUDE_DIR)/channel -type f -name "*.$(HPP_SRC_EXT)")\
			   $(addsuffix .$(HPP_SRC_EXT), $(addprefix $(INCLUDE_DIR)/gpio/, BaseGpioPin GenericGpioPin))\
			   $(shell find $(INCLUDE_DIR)/input -type f -name "*.$(HPP_SRC_EXT)")

IPP_FILES = $(shell find $(INCLUDE_DIR) -type f -name "*.$(IPP_SRC_EXT)")

SRC_FILES = $(addsuffix .$(CPP_SRC_EXT), $(addprefix $(SRC_DIR)/, elrond))\
			$(shell find $(SRC_DIR)/runtime -type f -name "*.$(CPP_SRC_EXT)")\
			$(shell find $(SRC_DIR)/module -type f -name "Base*.$(CPP_SRC_EXT)")\
			$(shell find $(SRC_DIR)/channel -type f -name "Rx*.$(CPP_SRC_EXT)" -or -name "Tx*$(CPP_SRC_EXT)")\
			$(shell find $(SRC_DIR)/gpio -type f -name "*.$(CPP_SRC_EXT)")\
			$(shell find $(SRC_DIR)/input -type f -name "*.$(CPP_SRC_EXT)")

HEADERS_DIST = $(subst $(INCLUDE_DIR)/,$(DIST_DIR)/,$(HEADER_FILES))
HEADERS_DIST += $(subst $(INCLUDE_DIR)/,$(DIST_DIR)/,$(addsuffix .$(HPP_SRC_EXT), $(IPP_FILES)))
SRC_DIST = $(subst $(SRC_DIR)/,$(DIST_DIR)/,$(subst .$(CPP_SRC_EXT),.$(IPP_SRC_EXT),$(SRC_FILES)))

VPATH = src: $(INCLUDE_DIR) $(SRC_DIR)
vpath %.$(HPP_SRC_EXT) $(INCLUDE_DIR)
vpath %.$(IPP_SRC_EXT) $(INCLUDE_DIR)
vpath %.$($(CPP_SRC_EXT)) $(SRC_DIR)

all: $(PROJECT_NAME).$(HPP_SRC_EXT)

$(PROJECT_NAME).$(HPP_SRC_EXT): $(DIST_DIR)/$(PROJECT_NAME).$(HPP_SRC_EXT)
$(DIST_DIR)/$(PROJECT_NAME).$(HPP_SRC_EXT): $(HEADERS_DIST) $(SRC_DIST)
	@mkdir -p $(@D)
	eval "echo '#ifndef _ELROND_HPP\n#define _ELROND_HPP'" > $@
	eval "cat $^ >> $@"
	eval "echo '#endif'" >> $@

$(DIST_DIR)/platform.$(HPP_SRC_EXT): $(INCLUDE_DIR)/platform.$(HPP_SRC_EXT)
	@mkdir -p $(@D)
	cp $^ $@
	eval "sed -i '/^\s*#include\s*\".*\"/d' $@"
	eval "sed -i '/^[[:space:]]*$$/d' $@"
	eval "sed -i 's/^\s*\/\/\s*#define\s*ELROND_WITH_INLINE_FUNC/    #define ELROND_WITH_INLINE_FUNC/g' $@"

$(DIST_DIR)/%.$(HPP_SRC_EXT): $(INCLUDE_DIR)/%.$(HPP_SRC_EXT)
	@mkdir -p $(@D)
	cp $^ $@
	eval "sed -i '/^\s*#include\s*\".*\"/d' $@"
	eval "sed -i '/^[[:space:]]*$$/d' $@"

$(DIST_DIR)/%.$(IPP_SRC_EXT).$(HPP_SRC_EXT): $(INCLUDE_DIR)/%.$(IPP_SRC_EXT)
	@mkdir -p $(@D)
	cp $^ $@
	eval "sed -i '/^\s*#include\s*\".*\"/d' $@"
	eval "sed -i '/^[[:space:]]*$$/d' $@"

$(DIST_DIR)/%.$(IPP_SRC_EXT): $(SRC_DIR)/%.$(CPP_SRC_EXT)
	@mkdir -p $(@D)
	cp $^ $@
	eval "sed -i '/^\s*#include\s*\".*\"/d' $@"
	eval "sed -i '/^[[:space:]]*$$/d' $@"
