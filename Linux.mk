################################################################################
#                              Linux build Rules                               #
################################################################################

# Include config file
include Config.mk

# Params lists
INCLUDES += $(i)
MACROS += $(m)

# Define object files
OBJS_FILES = $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(SRC_FILES))
OBJS := $(addsuffix .$(OBJ_EXT), $(OBJS_FILES))

# Set ext objects
OBJ_EXT_FILES = $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(SRC_EXT_FILES))
OBJS_EXT := $(addsuffix .$(OBJ_EXT), $(OBJ_EXT_FILES))

# Set test objects
OBJ_TEST_FILES = $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(SRC_TEST_FILES))
OBJS_EXT += $(addsuffix .$(OBJ_EXT), $(OBJ_TEST_FILES))

# Define dependencies files
DEPS = $(OBJS:.$(OBJ_EXT)=.$(DEP_EXT)) $($(OBJS_EXT:.$(OBJ_EXT)=.$(DEP_EXT)))

# Add includes and macros to compiler options
CXXFLAGS += $(addprefix -I, $(INCLUDES))
CXXFLAGS += $(addprefix -D, $(MACROS))

# Define paths and source file extensions
VPATH = src: $(SRC_DIR)
vpath %.$(CPP_SRC_EXT) $(SRC_DIR)
vpath %.$(C_SRC_EXT) $(SRC_DIR)

.PHONY: all clean

################################## BUILD RULES #################################

all: $(COMMON_STATIC_LIB) $(EXT_STATIC_LIB)

# Static library builder
$(COMMON_STATIC_LIB): $(OBJS)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $?

$(EXT_STATIC_LIB): $(OBJS_EXT)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $?

# Objects builder
$(BUILD_DIR)/%.cpp.$(OBJ_EXT): $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# Include all .d files
-include $(DEPS)
