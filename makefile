# Include config file
include Config.mk

# Search for all srcs and includes files
SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name "*.$(CPP_SRC_EXT)" -or -name "*.$(C_SRC_EXT)" \) )

# Define paths and source file extensions
VPATH = src: $(SRC_DIR)
vpath %.$(CPP_SRC_EXT) $(SRC_DIR)
vpath %.$(C_SRC_EXT) $(SRC_DIR)

.PHONY: all libelrond-dynamic libelrond-static clean test test-all
.DEFAULT_GOAL := all

################################## BUILD RULES #################################

# Include Platform target build rules
include $(TARGET_OS).mk

all: libelrond-dynamic libelrond-static
libelrond-dynamic: $(COMMON_SHARED_LIB)
libelrond-static: $(COMMON_STATIC_LIB)

clean:
	rm -rf $(BUILD_DIR)

test: $(COMMON_STATIC_LIB)
	@rm -f $(BUILD_DIR)/test/$(notdir $(basename $(t)))
	@$(MAKE) --no-print-directory -f $(TEST_MAKEFILE) run t="$(t)" l="$^" a="$a"

test-all: $(COMMON_STATIC_LIB)
	@rm -f $(BUILD_DIR)/test/all.test
	@$(MAKE) --no-print-directory -f $(TEST_MAKEFILE) all l="$^" a="$a"
