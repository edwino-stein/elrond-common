#Arduino general settings
LIBRARY_NAME = $(PROJECT_NAME)
DIST_DIR_ROOT = dist
LIBRARY_DIST_DIR = $(DIST_DIR_ROOT)/$(LIBRARY_NAME)
LIBRARY_SRC_DIR = $(LIBRARY_DIST_DIR)/src

# Define all files to the library
LIBRARY_INCLUDE_FILES = $(subst $(INCLUDE_DIR_ROOT)/,$(LIBRARY_SRC_DIR)/,$(INCLUDE_FILES))
LIBRARY_SRC_FILES = $(subst $(SRC_DIR_ROOT)/,$(LIBRARY_SRC_DIR)/,$(SRC_FILES))

# ************************** BUILD RULES **************************

.PHONY: arduino-dist clean-dist

# Prepare file structure like arduino IDE library specification (1.5.x)
arduino-dist: clean-dist $(LIBRARY_INCLUDE_FILES) $(LIBRARY_SRC_FILES)

# Copy headers
$(LIBRARY_SRC_DIR)/%.hpp: $(INCLUDE_DIR_ROOT)/%.hpp
	@mkdir -p $(@D)
	cp $< $@

$(LIBRARY_SRC_DIR)/%.h: $(INCLUDE_DIR_ROOT)/%.h
	@mkdir -p $(@D)
	cp $< $@

# Copy src
$(LIBRARY_SRC_DIR)/%.cpp: $(SRC_DIR_ROOT)/%.cpp
	@mkdir -p $(@D)
	cp $< $@

$(LIBRARY_SRC_DIR)/%.c: $(SRC_DIR_ROOT)/%.c
	@mkdir -p $(@D)
	cp $< $@

# Cleaner
clean-dist:
	rm -Rf $(DIST_DIR_ROOT)
