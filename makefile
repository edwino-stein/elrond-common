# Include config file
include Config.mk

# Define paths and source file extensions
VPATH = src: $(SRC_DIR)
vpath %.$(CPP_SRC_EXT) $(SRC_DIR)
vpath %.$(C_SRC_EXT) $(SRC_DIR)

.PHONY: all libelrond-dynamic libelrond-static libelrond-test libelrond-headeronly clean test test-all
.DEFAULT_GOAL := all

################################## BUILD RULES #################################

# Include Platform target build rules
include $(TARGET_OS).mk

all: libelrond-dynamic libelrond-static libelrond-test libelrond-headeronly
libelrond-dynamic: $(COMMON_SHARED_LIB)
libelrond-static: $(COMMON_STATIC_LIB) $(EXT_STATIC_LIB)
libelrond-test: $(TEST_STATIC_LIB)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_DIR)

libelrond-headeronly:
	@$(MAKE) --no-print-directory -f $(HO_MAKEFILE) all

test: libelrond-static libelrond-headeronly
	@rm -f $(BUILD_DIR)/test/$(notdir $(basename $(t)))
	@$(MAKE) --no-print-directory -f $(TEST_MAKEFILE) run t="$(t)" l="$(EXT_STATIC_LIB) $(COMMON_STATIC_LIB)" a="$a"

test-all: libelrond-static libelrond-headeronly
	@rm -f $(BUILD_DIR)/test/all.test
	@$(MAKE) --no-print-directory -f $(TEST_MAKEFILE) all l="$(EXT_STATIC_LIB) $(COMMON_STATIC_LIB)" a="$a"
