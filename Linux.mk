# General Linux build settings
BUILD_DIR_ROOT = build
OBJ_EXTENSION = .o
OBJ_PIC_EXTENSION = .PIC$(OBJ_EXTENSION)
RT_EXTENSION =
SO_EXTENSION = .so
DEPENDENCE_EXTENSION = .d

# Compiler and linker settings
COMPILER = g++
COMPILER_COMMON_OPTIONS = -std=c++11 -Wall -MMD -c
LIB_BUILDER = ar rvs

# Shared Library settings
COMPILER_SOL_OPTIONS = -fPIC

# Params lists
INCLUDES = $(INCLUDE_DIR_ROOT)
MACROS = GENERIC_STD_PLATFORM LINUX_PLATFORM $(m)

# Elrond COMMON library setup
COMMON_NAME_LIB = lib-$(PROJECT_NAME)
COMMON_PIC_LIB = $(COMMON_NAME_LIB).pic.a
COMMON_NOPIC_LIB = $(COMMON_NAME_LIB).a

#Define build dir as target for all src files
OBJS_FILES = $(subst $(SRC_DIR_ROOT)/,$(BUILD_DIR_ROOT)/,$(SRC_FILES))

# Set NOPIC objects
OBJS := $(addsuffix $(OBJ_EXTENSION), $(OBJS_FILES))
DEPS = $(OBJS:$(OBJ_EXTENSION)=$(DEPENDENCE_EXTENSION))

# Set PIC objects
OBJS_PIC := $(addsuffix $(OBJ_PIC_EXTENSION), $(OBJS_FILES))
DEPS += $(OBJS_PIC:$(OBJ_EXTENSION)=$(DEPENDENCE_EXTENSION))

# Add includes and macros to compiler options
COMPILER_COMMON_OPTIONS += $(addprefix -I, $(INCLUDES))
COMPILER_COMMON_OPTIONS += $(addprefix -D, $(MACROS))

.PHONY: $(COMMON_PIC_LIB) $(COMMON_NOPIC_LIB) clean-build
# ************************** BUILD RULES **************************

# PIC library builder
$(COMMON_PIC_LIB): $(BUILD_DIR_ROOT)/$(COMMON_PIC_LIB)
$(BUILD_DIR_ROOT)/$(COMMON_PIC_LIB): $(OBJS_PIC)
	@mkdir -p $(@D)
	@$(LIB_BUILDER) $@ $?

# PIC objects builder
$(BUILD_DIR_ROOT)/%$(OBJ_PIC_EXTENSION): $(SRC_DIR_ROOT)/%
	@mkdir -p $(@D)
	$(COMPILER) $(COMPILER_SOL_OPTIONS) $(COMPILER_COMMON_OPTIONS) $< -o $@

# NOPIC library builder
$(COMMON_NOPIC_LIB): $(BUILD_DIR_ROOT)/$(COMMON_NOPIC_LIB)
$(BUILD_DIR_ROOT)/$(COMMON_NOPIC_LIB): $(OBJS)
	@mkdir -p $(@D)
	@$(LIB_BUILDER) $@ $?

# Objects builder
$(BUILD_DIR_ROOT)/%$(OBJ_EXTENSION): $(SRC_DIR_ROOT)/%
	@mkdir -p $(@D)
	$(COMPILER) $(COMPILER_COMMON_OPTIONS) $< -o $@

clean-build:
	rm -rf $(BUILD_DIR_ROOT)

# Include all .d files
-include $(DEPS)
