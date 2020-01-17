################################################################################
#                              Linux build Rules                               #
################################################################################

# Params lists
INCLUDES += $(i)
MACROS += $(m)

# Elrond COMMON library setup
COMMON_SHARED_LIB = $(BUILD_DIR)/$(COMMON_NAME_LIB).$(DYNAMIC_LIB_EXT)
COMMON_STATIC_LIB = $(BUILD_DIR)/$(COMMON_NAME_LIB).$(STATIC_LIB_EXT)

# Define object files
OBJS_FILES = $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(SRC_FILES))
OBJS := $(addsuffix .$(OBJ_EXT), $(OBJS_FILES))

# Set PIC objects
OBJS_PIC := $(addsuffix .pic.$(OBJ_EXT), $(OBJS_FILES))

# Define dependencies files
DEPS = $(OBJS:.$(OBJ_EXT)=.$(DEP_EXT)) $(OBJS_PIC:.$(OBJ_EXT)=.$(DEP_EXT))

# Add includes and macros to compiler options
CXXFLAGS += $(addprefix -I, $(INCLUDES))
CXXFLAGS += $(addprefix -D, $(MACROS))

################################## BUILD RULES #################################

# Shared library builder
$(COMMON_SHARED_LIB): $(OBJS_PIC)
	@mkdir -p $(@D)
	$(CXX) -shared $(LDFLAGS) $^ -o $@

# PIC objects builder
$(BUILD_DIR)/%.cpp.pic.$(OBJ_EXT): $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -fPIC $(CXXFLAGS) -DPIC $< -o $@

# Static library builder
$(COMMON_STATIC_LIB): $(OBJS)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $?

# Objects builder
$(BUILD_DIR)/%.cpp.$(OBJ_EXT): $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

# Include all .d files
-include $(DEPS)
