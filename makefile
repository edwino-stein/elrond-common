# Include config file
include Config.mk

.PHONY: all libelrond-static libelrond-headeronly clean test test-all
.DEFAULT_GOAL := all

################################## BUILD RULES #################################

all: libelrond-static libelrond-headeronly

libelrond-static:
	@$(MAKE) --no-print-directory -f $(TARGET_OS).mk all

clean:
	@$(MAKE) --no-print-directory -f $(TARGET_OS).mk clean
	@$(MAKE) --no-print-directory -f $(HO_MAKEFILE) clean

libelrond-headeronly:
	@$(MAKE) --no-print-directory -f $(HO_MAKEFILE) all

test: libelrond-static libelrond-headeronly
	@rm -f $(BUILD_DIR)/test/$(notdir $(basename $(t)))
	@$(MAKE) --no-print-directory -f $(TEST_MAKEFILE) run t="$(t)" l="$(EXT_STATIC_LIB) $(COMMON_STATIC_LIB)" a="$a"

test-all: libelrond-static libelrond-headeronly
	@rm -f $(BUILD_DIR)/test/all.test
	@$(MAKE) --no-print-directory -f $(TEST_MAKEFILE) all l="$(EXT_STATIC_LIB) $(COMMON_STATIC_LIB)" a="$a"
