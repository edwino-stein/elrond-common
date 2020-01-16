# General Linux build settings
BUILD_DIR = build
OBJ_EXTENSION = .o
OBJ_PIC_EXTENSION = .pic$(OBJ_EXTENSION)
DEPENDENCE_EXTENSION = .d

# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -c
LDFLAGS = -std=c++11 -Wall
LDLIBS =
LD = ld
AR = ar
ARFLAGS = rvs

# Params lists
INCLUDES = $(INCLUDE_DIR)
MACROS = $(m)

# Elrond COMMON library setup
COMMON_NAME_LIB = lib$(PROJECT_NAME)
COMMON_PIC_LIB = $(COMMON_NAME_LIB)$(OBJ_PIC_EXTENSION)
COMMON_NONPIC_LIB = $(COMMON_NAME_LIB).a

# Define object files
OBJS_FILES = $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(SRC_FILES))
OBJS := $(addsuffix $(OBJ_EXTENSION), $(OBJS_FILES))

# Set PIC objects
OBJS_PIC := $(addsuffix $(OBJ_PIC_EXTENSION), $(OBJS_FILES))

# Define dependencies files
DEPS = $(OBJS:$(OBJ_EXTENSION)=$(DEPENDENCE_EXTENSION))
DEPS += $(OBJS_PIC:$(OBJ_EXTENSION)=$(DEPENDENCE_EXTENSION))

# Add includes and macros to compiler options
CXXFLAGS += $(addprefix -I, $(INCLUDES))
CXXFLAGS += $(addprefix -D, $(MACROS))

.PHONY: $(COMMON_PIC_LIB) $(COMMON_NONPIC_LIB) clean-build

# ************************** BUILD RULES **************************

# PIC library builder
$(COMMON_PIC_LIB): $(BUILD_DIR)/$(COMMON_PIC_LIB)
$(BUILD_DIR)/$(COMMON_PIC_LIB): $(OBJS_PIC)
	@mkdir -p $(@D)
	$(LD) -r $^ -o $@

# PIC objects builder
$(BUILD_DIR)/%.cpp$(OBJ_PIC_EXTENSION): $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -fPIC $(CXXFLAGS) -DPIC $< -o $@

# NOPIC library builder
$(COMMON_NONPIC_LIB): $(BUILD_DIR)/$(COMMON_NONPIC_LIB)
$(BUILD_DIR)/$(COMMON_NONPIC_LIB): $(OBJS)
	@mkdir -p $(@D)
	@$(AR) $(ARFLAGS) $@ $?

# Objects builder
$(BUILD_DIR)/%.cpp$(OBJ_EXTENSION): $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

clean-build:
	rm -rf $(BUILD_DIR)

# Include all .d files
-include $(DEPS)
